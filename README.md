# ltabs
Панель рабочего стола с поддержкой собственных расширений (QT, QML) для GNU/Linux.

##### Лицензия:
Программа распространяется под лицензией GPLv3
В программе используются иконки Mono Dark Flattr:
https://github.com/hai-nguyen-van/mono-dark-flattr-icons
распространяемых под лицензией CC BY-SA 4.0
Ссылка на лицензию https://raw.githubusercontent.com/hai-nguyen-van/mono-dark-flattr-icons/master/LICENSE
В некоторые иконки внесены изменения с целью адаптации к приложению.

##### Подготовка к сборке:
Установить библиотеку KWindowSystem:
```
# apt install libkf5windowsystem-dev
```
В QT Creator для сборочного комплекта выбрать системный профиль QT (qmake). В Ubuntu 18.04 размещён по пути `/usr/lib/qt5/bin/qmake`
Сборка выполняется стандартыми средствами QT Creator.

##### Конфигурация
Настройки программы сохраняются в INI-файле `~/.config/ltabs/ltabs.conf`
Большинство настроек можно задать через интерфейс программы. Настройки, перечисленные ниже, задаются непосредственно в конфигурационном файле:

Секция `[UI]`

`max_width` - значение по умолчанию 400, задаёт максимальную ширину главного окна в пикселях;

`min_width` - значение по умолчанию 160, задаёт минимальную ширину главного окна в пикселях;

`max_control_buttons_width` - значение по умолчанию 64, задаёт максимальный размер кнопок панели управления в пикселях;

`min_control_buttons_width` - значение по умолчанию 24, задаёт минимальный размер кнопок панели управления в пикселях;
