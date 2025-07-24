@echo off
REM Generate CalTag patterns - Windows wrapper script
REM Creates temporary virtual environment, installs dependencies, runs script, then cleans up

setlocal EnableDelayedExpansion

REM Get script directory
set "SCRIPT_DIR=%~dp0"
set "PYTHON_SCRIPT=%SCRIPT_DIR%calTagPatternGenerator.py"

REM Check if Python script exists
if not exist "%PYTHON_SCRIPT%" (
    echo Error: calTagPatternGenerator.py not found in %SCRIPT_DIR%
    exit /b 1
)

REM Check for required arguments
if "%~2"=="" (
    echo Usage: %0 ^<width^> ^<height^> [additional_args...]
    echo Example: %0 95 47 -c -o mycaltag.pdf
    exit /b 1
)

REM Create temporary directory for virtual environment
set "TEMP_DIR=%TEMP%\caltag_temp_%RANDOM%"
set "VENV_DIR=%TEMP_DIR%\caltag_venv"

echo Setting up temporary environment in %TEMP_DIR%

REM Create temp directory
mkdir "%TEMP_DIR%" 2>nul

REM Check if python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo Error: Python is required but not installed or not in PATH
    rmdir /s /q "%TEMP_DIR%" 2>nul
    exit /b 1
)

REM Create virtual environment
echo Creating virtual environment...
python -m venv "%VENV_DIR%"
if errorlevel 1 (
    echo Error: Failed to create virtual environment
    rmdir /s /q "%TEMP_DIR%" 2>nul
    exit /b 1
)

REM Activate virtual environment
call "%VENV_DIR%\Scripts\activate.bat"

REM Upgrade pip
echo Upgrading pip...
python -m pip install --upgrade pip --quiet

REM Install required packages
echo Installing required packages...
pip install reportlab numpy --quiet
if errorlevel 1 (
    echo Error: Failed to install required packages
    call "%VENV_DIR%\Scripts\deactivate.bat" 2>nul
    rmdir /s /q "%TEMP_DIR%" 2>nul
    exit /b 1
)

REM Copy Python script to temp directory
copy "%PYTHON_SCRIPT%" "%TEMP_DIR%\" >nul

REM Change to temp directory
pushd "%TEMP_DIR%"

REM Run the Python script with all provided arguments
echo Running CalTag generator...
python calTagPatternGenerator.py %*
set "PYTHON_EXIT_CODE=!errorlevel!"

REM Copy generated files back to original directory
echo Copying generated files back...
for %%f in (*.pdf *.c) do (
    if exist "%%f" (
        copy "%%f" "%SCRIPT_DIR%" >nul
        echo Generated: %SCRIPT_DIR%%%f
    )
)

REM Return to original directory
popd

REM Deactivate virtual environment
call "%VENV_DIR%\Scripts\deactivate.bat" 2>nul

REM Cleanup temporary files
echo Cleaning up temporary files...
rmdir /s /q "%TEMP_DIR%" 2>nul

if !PYTHON_EXIT_CODE! equ 0 (
    echo CalTag generation complete!
) else (
    echo CalTag generation failed with exit code !PYTHON_EXIT_CODE!
    exit /b !PYTHON_EXIT_CODE!
)

echo Cleanup complete.