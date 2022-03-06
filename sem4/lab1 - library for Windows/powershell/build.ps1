$BuildFolder = "build" 
$ExecutableName = "math.exe"

function Check-Command($Command) {
    return [bool](Get-Command -Name $Command -ErrorAction SilentlyContinue)
}

function Build-Number {
    echo "Building Number:"
    echo "g++ -c Number/Number.cpp -o build/Number.o"
    g++ -c Number/Number.cpp -o build/Number.o
    echo "ar rvs build/Number.lib build/Number.o"
    ar rvs build/Number.lib build/Number.o
    echo "[DONE]"
    echo ""
}

function Build-Vector {
    echo "Building Vector:"
    echo "g++ -c -INumber Vector/Vector.cpp -o build/Vector.o"
    g++ -c -INumber Vector/Vector.cpp -o build/Vector.o
    echo "g++ -shared -o build/libVector.dll build/Vector.o build/Number.lib"
    g++ -shared -o build/libVector.dll build/Vector.o build/Number.lib
    echo "[DONE]"
    echo ""
}

function Build-App {
    echo "Building App:"
    echo "g++ -INumber -IVector -Lbuild/ -lVector App/main.cpp -o build/$ExecutableName"
    g++ -INumber -IVector -Lbuild/ -lVector App/main.cpp -o build/$ExecutableName
    echo "[DONE]"
    echo ""
}

function Build {
    if (-Not (Test-Path -Path $BuildFolder)) {
        mkdir $BuildFolder
    }
    Build-Number
    Build-Vector
    Build-App   
}

function Clean{
    echo "Cleaning build files"
    if (Test-Path -Path $BuildFolder) {
        rm -r $BuildFolder
    }
    echo "[DONE]"
    echo ""
}

function Run {   
    echo "Running the project at $BuildFolder/${ExecutableName}:"
    if (Test-Path -Path $BuildFolder/$ExecutableName) {
        &".\build\$ExecutableName"
    } else {
        echo "$ExecutableName not found. Firstly, consider building the project."
    }
    echo "[DONE]"
    echo ""
}

foreach($Command in $args) {
    if (Check-Command -Command $Command) {
        &$Command
    } else {
        echo "No target $Command"
    }
} 
