#!/bin/bash
set -e

echo "🔨 Установка DWM 6.5 с патчами systray и autostart..."

# Переход в каталог с исходниками
cd "$(dirname "$0")/src/dwm-6.5"

# Проверка наличия config.h
if [ ! -f config.h ]; then
    echo "❌ Файл config.h не найден!"
    exit 1
fi

# Очистка предыдущей сборки
make clean

# Сборка и установка
sudo make install

echo "✅ DWM успешно установлен в /usr/local/bin/dwm"
echo "💡 Для применения изменений перезапустите X-сессию"
echo "🔧 Используйте 'sudo systemctl restart gdm' или перезагрузитесь"
