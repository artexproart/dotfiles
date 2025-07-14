#!/bin/bash

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
GNOME_CONFIG_DIR="$REPO_DIR/config/gnome"

echo "Восстановление GNOME настроек..."

# Проверить наличие файлов
if [ ! -f "$GNOME_CONFIG_DIR/dconf-backup/complete-settings.dconf" ]; then
    echo "✗ Файл dconf настроек не найден!"
    exit 1
fi

# Создать backup текущих настроек
echo "Создание backup текущих настроек..."
BACKUP_DIR="$HOME/.config/backup-$(date +%Y%m%d-%H%M%S)"
mkdir -p "$BACKUP_DIR"
dconf dump / > "$BACKUP_DIR/current-settings.dconf"
echo "✓ Backup создан в: $BACKUP_DIR"

# Восстановить dconf настройки
echo "Восстановление dconf настроек..."
dconf load / < "$GNOME_CONFIG_DIR/dconf-backup/complete-settings.dconf"

# Восстановить конфигурации приложений
echo "Восстановление конфигурационных файлов..."
rsync -av "$GNOME_CONFIG_DIR/config/" ~/.config/ 2>/dev/null || true

# Установить правильные права доступа
chmod -R 755 ~/.config

echo "✓ GNOME настройки восстановлены"
echo "Для полного применения настроек перезайдите в сессию:"
echo "gnome-session-quit --logout"

