#!/bin/bash

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"

GNOME_CONFIG_DIR="$REPO_DIR/config/gnome"

echo "Синхронизация GNOME настроек..."

# Обновить dconf backup
echo "Обновление dconf настроек..."
dconf dump / > "$GNOME_CONFIG_DIR/dconf-backup/complete-settings.dconf"

# Обновить конфигурации приложений
echo "Обновление конфигурационных файлов..."
rsync -av --delete --exclude="cache" --exclude="Cache" --exclude="logs" --exclude="tmp" \
    ~/.config/gtk-3.0/ "$GNOME_CONFIG_DIR/config/gtk-3.0/" 2>/dev/null || true
rsync -av --delete ~/.config/gtk-4.0/ "$GNOME_CONFIG_DIR/config/gtk-4.0/" 2>/dev/null || true
rsync -av --delete ~/.config/dconf/ "$GNOME_CONFIG_DIR/config/dconf/" 2>/dev/null || true

# Добавить изменения в git
cd "$REPO_DIR"
git add config/gnome/

# Проверить есть ли изменения
if git diff --cached --quiet; then
    echo "Нет изменений для синхронизации"
else
    echo "Найдены изменения GNOME настроек..."
    git commit -m "Update GNOME settings $(date '+%Y-%m-%d %H:%M:%S')"
    echo "✓ GNOME настройки синхронизированы"
fi

