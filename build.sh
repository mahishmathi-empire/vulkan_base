build_package() {
    # Define options
    local OPTS=$(getopt -o cp:i --long clean,package:,install -n 'build_package' -- "$@")
    if [ $? != 0 ]; then echo "Failed parsing options." >&2; exit 1; fi

    eval set -- "$OPTS"

    local clean_build_flag=0
    local install_flag=0
    local package_name=""
    local additional_args=()

    # Extract options and their arguments
    while true; do
        case "$1" in
            -c | --clean )
                clean_build_flag=1; shift ;;
            -p | --package )
                package_name="$2"; shift; shift ;;
            -i | --install )
                install_flag=1; shift ;;
            -- )
                shift; break ;;
            * )
                break ;;
        esac
    done
    
    # The rest of the arguments are considered additional arguments for cmake
    additional_args=("$@")

    if [[ -z "$package_name" ]]; then
        echo "Please provide a package name."
        return 1
    fi

    # Start searching for the workspace root from the current directory
    local current_dir=$(pwd)
    local return_dir=$(pwd)
    local workspace_base=""

    while [[ "$current_dir" != '/' ]]; do
        if [[ -d "$current_dir/src" && -d "$current_dir/build" ]]; then
            workspace_base="$current_dir"
            break
        fi
        current_dir=$(dirname "$current_dir")
    done

    if [[ -z "$workspace_base" ]]; then
        echo "Workspace root with 'src' and 'build' directories not found."
        return 1
    fi

    local src_dir=""
    # Dynamically find the package's source directory
    # Look directly under src and then one level deeper
    if [[ -d "${workspace_base}/src/${package_name}" ]]; then
        src_dir="${workspace_base}/src/${package_name}"
    else
        # Search one level deeper
        local found=$(find "${workspace_base}/src" -maxdepth 2 -type d -name "${package_name}" -print -quit)
        if [[ -n "$found" ]]; then
            src_dir=$found
        fi
    fi

    local build_dir="${workspace_base}/build/${package_name}"
    local install_dir="${workspace_base}/install"

    # Check if the source directory exists
    if [[ ! -d "$src_dir" ]]; then
        echo "Source directory for package '${package_name}' does not exist."
        return 1
    fi

    # Clean build directory if flag is set
    if [[ "$clean_build_flag" == 1 ]]; then
        echo "Cleaning build directory for package '${package_name}'."
        rm -rf "$build_dir"/
    fi

    # Create the build directory if it doesn't exist
    if [[ ! -d "$build_dir" ]]; then
        echo "Creating build directory for package '${package_name}'."
        mkdir -p "$build_dir"
    fi

    # Navigate to the build directory
    cd "$build_dir" || return

    # Run CMake with the specified configurations
    echo "Running cmake for package '${package_name}'..."
    cmake -DCMAKE_INSTALL_PREFIX="${install_dir}" "${additional_args}" "$src_dir"

    # Install if flag
    if [[ "$install_flag" == 1 ]]; then
        echo "Installing package '${package_name}'."
        make install -j16
    fi

    # Navigate back to the original directory
    cd "$return_dir" || return
}

# Run the build_package function with the provided arguments
build_package "$@"