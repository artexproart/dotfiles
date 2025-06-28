# README.md - Документация dotfiles для Ubuntu 24.04

Полная система управления конфигурационными файлами с использованием GNU Stow для воспроизводимой рабочей среды на базе DWM 6.5.

## 📋 Содержание

- [Обзор системы](#обзор-системы)
- [Быстрый старт](#быстрый-старт)
- [Установленные компоненты](#установленные-компоненты)
- [Структура репозитория](#структура-репозитория)
- [Пошаговое развертывание](#пошаговое-развертывание)
- [Управление конфигами](#управление-конфигами)
- [Устранение неполадок](#устранение-неполадок)

## 🎯 Обзор системы

Этот репозиторий содержит полную конфигурацию рабочей среды для Ubuntu 24.04, включающую:

- **DWM 6.5** - тайловый оконный менеджер с патчами systray и autostart
- **Терминал и редактор** - Alacritty + Neovim с AstroNvim
- **Системные утилиты** - настроенные апплеты трея и автозапуск
- **Пользовательские приложения** - Obsidian, Яндекс.Музыка и другие

Все конфигурации управляются через **GNU Stow** для создания символических ссылок, что обеспечивает централизованное управление и простое развертывание на новых машинах.


## Пакет settings

Пакет `settings` содержит централизованные конфиги для темной темы:
- `.config/gtk-3.0/settings.ini`
- `.config/gtk-4.0/settings.ini`
- `.config/xsettingsd/xsettingsd.conf`
- `.xprofile` (запуск xsettingsd)


## 🚀 Быстрый старт

### Требования
- Ubuntu 24.04 LTS
- Git и SSH настроены для GitHub
- Права sudo для установки пакетов

### Установка на новой системе

```bash
# 1. Клонирование репозитория
git clone git@github.com:artexproart/dotfiles.git ~/dotfiles

# 2. Установка GNU Stow
sudo apt update && sudo apt install stow

# 3. Применение всех конфигов
cd ~/dotfiles
stow bash git alacritty nvim xsession obsidian yandex-music apps settings

# 4. Установка и сборка DWM
./dwm/install.sh
```

## 📦 Установленные компоненты

### Системные компоненты
- **DWM 6.5** - оконный менеджер с патчами
- **Alacritty** - терминальный эмулятор (конфиг в формате TOML)
- **FiraCode Nerd Font** - шрифт для программирования

### Инструменты разработки
- **Neovim 0.11.2** с конфигурацией AstroNvim
- **Git** с настроенным SSH для GitHub
- **Bash** с кастомными настройками и алиасами

### Утилиты и апплеты
- **lazygit-gm** - консольный интерфейс для Git
- **bottom** - мониторинг системных ресурсов
- **copyq** - менеджер буфера обмена
- **volumeicon** - управление громкостью
- **nm-applet** - управление сетью
- **kbdd + kbdd-indicator** - индикатор раскладки клавиатуры

## Пользовательские приложения
- **Obsidian** - управление знаниями
- **Яндекс.Музыка 5.53.1** - музыкальный плеер
- **Google Chrome** - веб-браузер
- **Telegram Desktop** - мессенджер

### Веб-приложения Chrome
Следующие веб-сервисы установлены как отдельные приложения Chrome и доступны через Rofi:

#### Образовательные платформы
- **Stepik** (https://stepik.org/) — онлайн-курсы и обучение
- **Hexlet** (https://ru.hexlet.io/my) — IT-образование и практика

#### Инструменты разработки
- **Yandex Cloud Console** (https://console.yandex.cloud/) — управление облачными ресурсами
- **Klava.org** (https://klava.org/) — тренажер слепой печати

#### Искусственный интеллект
- **Perplexity AI** (https://www.perplexity.ai/) — ИИ-помощник для поиска и анализа

### Использование
1. Запустите любое приложение через Rofi
2. Начните вводить название приложения
3. Приложение откроется в отдельном окне без браузерного интерфейса

### Файлы конфигурации
- Все `.desktop` файлы Chrome-приложений хранятся в `apps/.local/share/applications/`

## 📁 Структура репозитория

```
dotfiles/
├── README.md                    # Эта документация
├── .gitignore                   # Исключения для Git
├── bash/                        # Конфигурация Bash
│   ├── .bashrc                  # Основные настройки shell
│   ├── .bash_logout             # Скрипт завершения сессии
│   └── .profile                 # Переменные окружения
├── git/                         # Настройки Git
│   └── .gitconfig               # Пользовательские настройки Git
├── alacritty/                   # Конфигурация терминала
│   └── .config/alacritty/
│       └── alacritty.toml       # Настройки Alacritty (TOML формат)
├── nvim/                        # Конфигурация Neovim
│   └── .config/nvim/            # AstroNvim с LSP серверами
│       ├── init.lua             # Главный конфиг Neovim
│       └── lua/                 # Lua модули и плагины
├── xsession/                    # Системные скрипты
│   └── .xsessionrc              # Автозапуск DWM и апплетов
├── dwm/                         # Исходники и конфиги DWM
│   ├── install.sh               # Скрипт сборки и установки
│   ├── patches/                 # Патчи для DWM
│   │   └── dwm-systray-20230922-9f88553.diff
│   └── src/dwm-6.5/             # Исходные коды DWM 6.5
│       ├── config.h             # Кастомная конфигурация
│       ├── dwm.c                # Основные исходники
│       └── Makefile             # Файл сборки
├── obsidian/                    # Настройки Obsidian
│   └── .config/obsidian/
│       └── obsidian.json        # Конфигурация приложения
└── yandex-music/                # Настройки Яндекс.Музыки
├── settings/                    # Dark theme settings (GTK3/4, xsettingsd, .xprofile)
    └── .config/
        ├── yandex-music/
        │   └── config.json      # Настройки приложения
        └── yandex-music.conf    # Дополнительная конфигурация
```

## 🔧 Пошаговое развертывание

### 1. Подготовка системы

```bash
# Обновление пакетов
sudo apt update && sudo apt upgrade -y

# Установка зависимостей для сборки DWM
sudo apt install -y build-essential libx11-dev libxft-dev libxinerama-dev

# Установка базовых утилит
sudo apt install -y git stow curl
```

### 2. Установка Neovim 0.11.2

```bash
# Загрузка и установка Neovim
curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim-linux64.tar.gz
sudo rm -rf /opt/nvim
sudo tar -C /opt -xzf nvim-linux64.tar.gz
echo 'export PATH="$PATH:/opt/nvim/bin"' >> ~/.bashrc
```

### 3. Установка шрифта FiraCode Nerd Font

```bash
mkdir -p ~/.local/share/fonts
cd ~/.local/share/fonts
wget https://github.com/ryanoasis/nerd-fonts/releases/download/v3.0.2/FiraCode.zip
unzip FiraCode.zip
fc-cache -fv
```

### 4. Клонирование и применение dotfiles

```bash
# Клонирование репозитория
git clone git@github.com:artexproart/dotfiles.git ~/dotfiles
cd ~/dotfiles

# Применение конфигов через Stow
stow bash git alacritty nvim xsession obsidian yandex-music apps settings apps
```

### 5. Сборка и установка DWM

```bash
# Запуск скрипта установки DWM
cd ~/dotfiles
chmod +x dwm/install.sh
./dwm/install.sh
```

### 6. Установка дополнительных утилит

```bash
# Системные апплеты
sudo apt install -y network-manager-gnome blueman volumeicon-alsa

# Утилиты для работы
sudo apt install -y copyq

# Приложения
sudo snap install obsidian --classic
# Яндекс.Музыка устанавливается отдельно с официального сайта
```

## 🛠 Управление конфигами

### Добавление нового конфига

```bash
cd ~/dotfiles

# Создание структуры для нового приложения
mkdir -p new-app/.config/new-app

# Копирование конфига
cp ~/.config/new-app/config.file new-app/.config/new-app/

# Применение через Stow
stow new-app

# Добавление в Git
git add new-app
git commit -m "Добавлен конфиг для new-app"
git push
```

### Обновление существующих конфигов

```bash
cd ~/dotfiles

# Проверка статуса
git status

# Добавление изменений
git add .
git commit -m "Обновлены конфиги"
git push
```

### Удаление конфига

```bash
cd ~/dotfiles

# Удаление символических ссылок
stow -D app-name

# Удаление из репозитория
rm -rf app-name
git add .
git commit -m "Удален конфиг app-name"
git push
```

## 🔧 Конфигурация DWM

### Основные горячие клавиши

| Комбинация | Действие |
|------------|----------|
| `Mod + Return` | Открыть терминал |
| `Mod + r | Запуск dmenu/rofi |
| `Mod + j/k` | Переключение между окнами |
| `Mod + h/l` | Изменение размера главного окна |
| `Mod + [1-9]` | Переключение тегов (рабочих столов) |
| `Mod + Shift + [1-9]` | Перемещение окна на тег |
| `Mod + Shift + c` | Закрытие окна |
| `Mod + Shift + q` | Выход из DWM |

### Автозапуск приложений

Скрипт `~/.xsessionrc` автоматически запускает:
- Настройки мыши Logitech G403
- Апплеты системного трея
- Строку статуса с датой и временем
- DWM оконный менеджер

## 🐛 Устранение неполадок

### Проблемы с симлинками

```bash
# Проверка существующих симлинков
ls -la ~/.bashrc ~/.gitconfig

# Пересоздание симлинков
cd ~/dotfiles
stow -R app-name
```

### Конфликты при установке

```bash
# Удаление конфликтующих файлов
rm ~/.config/app/config.file

# Повторное применение
stow app-name
```

### Проблемы с DWM

```bash
# Пересборка DWM
cd ~/dotfiles/dwm/src/dwm-6.5
sudo make clean install

# Проверка установки
which dwm
dwm -v
```

### Проблемы с Neovim

```bash
# Проверка версии
nvim --version

# Обновление плагинов AstroNvim
nvim +AstroUpdate
```

## 📝 Дополнительные настройки

### Настройка SSH для GitHub

```bash
# Генерация SSH ключа
ssh-keygen -t ed25519 -C "your-email@example.com"

# Добавление ключа в ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# Добавление публичного ключа в GitHub
cat ~/.ssh/id_ed25519.pub
```

### Настройка мыши Logitech G403
Настройки мыши автоматически применяются через `~/.xsessionrc`:
```bash
xinput set-prop "Logitech G403 HERO Gaming Mouse" "libinput Accel Speed" -1
```

### Раскладка клавиатуры
US/RU раскладки с переключением по Alt+Shift настраиваются автоматически через `kbdd`.
- Управляются через GNU Stow командой `stow apps`

## 📄 Лицензия
Этот репозиторий содержит персональные конфигурационные файлы. Используйте на свой страх и риск.

---

**Автор:** artexproart  
**Репозиторий:** https://github.com/artexproart/dotfiles  
**Система:** Ubuntu 24.04 LTS + DWM 6.5
