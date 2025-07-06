# DWM Configuration для Ubuntu 24.04

Полная конфигурация рабочего окружения на базе DWM (Dynamic Window Manager) для Ubuntu 24.04 LTS с системным треем, семантическими тегами и автозапуском приложений.

## Содержание

- [Обзор системы](#обзор-системы)
- [Быстрый старт](#быстрый-старт)
- [Конфигурация DWM](#конфигурация-dwm)
- [Автозапуск приложений](#автозапуск-приложений)
- [Горячие клавиши](#горячие-клавиши)
- [Управление системой](#управление-системой)
- [Устранение неполадок](#устранение-неполадок)

## Обзор системы

### Характеристики
- **ОС**: Ubuntu 24.04 LTS
- **WM**: DWM 6.5 с патчем systray
- **Терминал**: Alacritty
- **Редактор**: Neovim с AstroNvim
- **Шрифт**: FiraCode Nerd Font

### Семантические теги (рабочие пространства)
- **1: Search** - Google Chrome autostart
- **2: Work** - Рабочие задачи и терминалы
- **3: Planing** планирование
- **4: Notes** 
- **5: AI**  
- **6: Study**  
- **7: Training** - Тренинги и семинары
- **8: Chats** - Мессенджеры и коммуникации
- **9: Music** - Яндекс.Музыка и аудио

### Системный трей
- **nm-applet** - управление сетью
- **volumeicon** - индикатор громкости
- **copyq** - менеджер буфера обмена
- **Статус-строка** - дата и время

## Быстрый старт

```bash
# Клонировать репозиторий
git clone https://github.com/yourusername/dotfiles.git ~/dotfiles

# Установить DWM
cd ~/dotfiles/dwm
sudo ./install.sh

# Настроить автозапуск
ln -sf ~/dotfiles/xsession/.xsessionrc ~/.xsessionrc

# Настроить конфигурации приложений
ln -sf ~/dotfiles/config/alacritty.yml ~/.config/alacritty/alacritty.yml

# Выйти и войти в сессию DWM
```

## Конфигурация DWM

### Исходники и сборка
```bash
# Расположение исходников
~/src/dwm-6.5/

# Команды сборки
cd ~/src/dwm-6.5
sudo make clean install
```

### Примененные патчи
- **systray** - системный трей (версия 20230922-9f88553)

### Настройки системного трея
```c
static const int showsystray = 1;                 // Включить трей
static const unsigned int systrayspacing = 8;     // Отступы между иконками
static const unsigned int systrayonleft = 3;      // Позиция трея
```

### Правила размещения окон
```c
static const Rule rules[] = {
    /* class            tags mask     isfloating */
    { "google-chrome",  1  /dev/null 2>&1 &
volumeicon > /dev/null 2>&1 &
copyq > /dev/null 2>&1 &

# Статус-строка
while true; do
    xsetroot -name "$(date '+%a %d %b %H:%M')"
    sleep 30
done &

# Запуск DWM
exec /usr/local/bin/dwm
```

## Горячие клавиши

### Основные действия
| Комбинация | Действие |
|------------|----------|
| `Win + R` | Rofi (меню приложений) |
| `Win + Shift + Enter` | Терминал (Alacritty) |
| `Win + N` | Neovim в терминале |
| `Win + V` | VS Code |
| `Win + G` | Google Chrome |
| `Win + O` | Obsidian |
| `Win + Y` | Яндекс.Музыка |

### Навигация по тегам
| Комбинация | Действие |
|------------|----------|
| `Win + 1-9` | Переключение на тег |
| `Win + ←` | Предыдущий тег (циклично) |
| `Win + →` | Следующий тег (циклично) |
| `Win + Shift + 1-9` | Переместить окно на тег |

### Управление окнами
| Комбинация | Действие |
|------------|----------|
| `Win + J/K` | Фокус на следующее/предыдущее окно |
| `Win + H/L` | Изменить размер мастер-области |
| `Win + Shift + C` | Закрыть окно |
| `Win + Space` | Переключить раскладку |
| `Win + Shift + Space` | Плавающий режим |

### Скриншоты
| Комбинация | Действие |
|------------|----------|
| `Win + Shift + S` | Скриншот области |
| `Win + Shift + Print` | Скриншот экрана |
| `Print` | Скриншот экрана |

### Система
| Комбинация | Действие |
|------------|----------|
| `Win + Shift + Q` | Выйти из DWM |
| `Win + B` | Показать/скрыть панель |
| `Alt + Shift` | Переключить раскладку |

## Управление системой

### Перезапуск DWM
```bash
# Быстрый перезапуск
Win + Shift + Q

# Или через терминал
pkill dwm
```

### Обновление конфигурации
```bash
cd ~/src/dwm-6.5
# Редактировать config.h
nvim config.h
# Пересобрать
sudo make clean install
# Перезапустить DWM
```

### Управление автозапуском
```bash
# Редактировать автозапуск
nvim ~/.xsessionrc

# Проверить запущенные процессы
ps aux | grep -E "(nm-applet|volumeicon|copyq)"
```

## Устранение неполадок

### DWM не запускается
```bash
# Проверить установку
which dwm
ls -la /usr/local/bin/dwm

# Проверить логи
journalctl -f
```

### Системный трей не работает
```bash
# Проверить патч systray
grep -i systray ~/src/dwm-6.5/dwm.c

# Перезапустить апплеты
pkill nm-applet volumeicon copyq
nm-applet &
volumeicon &
copyq &
```

### Автозапуск не работает
```bash
# Проверить файл автозапуска
ls -la ~/.xsessionrc
cat ~/.xsessionrc

# Проверить права
chmod +x ~/.xsessionrc
```

### Горячие клавиши не работают
```bash
# Проверить конфигурацию
grep -A 20 "static const Key keys" ~/src/dwm-6.5/config.h

# Пересобрать DWM
cd ~/src/dwm-6.5
sudo make clean install
```

### Проблемы со шрифтами
```bash
# Обновить кэш шрифтов
fc-cache -fv

# Проверить доступные шрифты
fc-list | grep -i fira
```

## Дополнительные настройки

### Настройка мыши
```bash
# Список устройств
xinput list

# Настройка чувствительности
xinput set-prop "Logitech G403 HERO Gaming Mouse" "libinput Accel Speed" -1
```

### Настройка раскладки клавиатуры
```bash
# Установить раскладки
setxkbmap -layout "us,ru" -option "grp:alt_shift_toggle"

# Проверить текущую раскладку
setxkbmap -query
```

### Управление звуком
```bash
# Настройка через volumeicon
# Клик по иконке в трее

# Командная строка
amixer set Master 5%+
amixer set Master 5%-
amixer set Master toggle
```

**Автор**: art@home  
**Версия**: 2025.06  
**Лицензия**: MIT

**Автор:** artexproart  
**Репозиторий:** https://github.com/artexproart/dotfiles  
**Система:** U:Жbuntu 24.04 LTS + DWM 6.5

### YouGile

- Приложение YouGile установлено как AppImage и запускается с параметром --no-sandbox.
- Для удобного запуска через Rofi создан ярлык с .desktop файлом.
- Файл .desktop находится в пакете apps и управляется через GNU Stow.

Использование:
1. Нажмите Mod + r для вызова Rofi.
2. Начните вводить "YouGile".
3. Выберите приложение для запуска.

