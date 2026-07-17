# 3D Engine - WWW

Choose language / Выберите язык: [English](#english) | [Русский](#русский)

---

## English

### Project Layout
* The project build appears in the `build/bin` directory after compilation.
* The engine features its own resource manager. Upon compilation, a `res` folder containing all dependencies is added to the `build/bin` directory alongside the `.exe` file.

### CMake Commands

Use the PowerShell console in VS Code to generate CMake files.

**1. Generate build files**
You need to create a `build` folder, navigate into it using `cd`, and run:
```bash
cmake -G "MinGW Makefiles" ..
```

**2. Clean up CMake files**
```powershell
Remove-Item -Recurse -Force CMakeCache.txt, CMakeFiles
```

**3. Build the project via console**
You must be in the project root folder. *(Note: If you are already inside the `build` folder, you can use `cmake --build .` instead)*:
```bash
cmake --build build
```

**4. Reset build configuration settings**
```bash
cmake -B build
```

---

## Русский

### Структура проекта
* Билд проекта после компиляции появляется в директории `build/bin`.
* В движке есть свой менеджер ресурсов. При компиляции проекта, помимо `.exe` файла, в директорию `build/bin` также копируется папка `res` со всеми зависимостями.

### Команды CMake

Для генерации файлов CMake используйте консоль PowerShell в VS Code.

**1. Генерация файлов сборки**
Необходимо создать папку `build`, войти в нее через `cd` и ввести команду:
```bash
cmake -G "MinGW Makefiles" ..
```

**2. Очистка файлов CMake**
```powershell
Remove-Item -Recurse -Force CMakeCache.txt, CMakeFiles
```

**3. Сборка проекта через консоль**
Команду нужно запускать из корневой папки проекта. *(Если вы уже находитесь в папке `build`, используйте `cmake --build .`)*:
```bash
cmake --build build
```

**4. Сброс настроек конфигурации сборки**
```bash
cmake -B build
```
