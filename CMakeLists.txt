cmake_minimum_required(VERSION 3.16)
project(fonction)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(fonction
	main.cpp
	MainWindow.cpp
	)

target_link_libraries(fonction Qt5::Core Qt5::Widgets)

# Configuration RPATH pour trouver les bibliothèques dans ./lib
set_target_properties(fonction PROPERTIES
    INSTALL_RPATH "$ORIGIN/lib"
    BUILD_WITH_INSTALL_RPATH TRUE
)

# Créer un script de déploiement séparé
file(WRITE ${CMAKE_BINARY_DIR}/deploy_qt.sh
"#!/bin/bash
echo '=== Déploiement automatique des bibliothèques Qt5 ==='

# Créer les répertoires
mkdir -p lib plugins

# Copier les bibliothèques Qt5 principales
echo 'Copie des bibliothèques Qt5...'
cp /usr/lib/x86_64-linux-gnu/libQt5Core.so.5 lib/ 2>/dev/null && echo '✓ libQt5Core.so.5' || echo '✗ libQt5Core.so.5'
cp /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5 lib/ 2>/dev/null && echo '✓ libQt5Widgets.so.5' || echo '✗ libQt5Widgets.so.5'
cp /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5 lib/ 2>/dev/null && echo '✓ libQt5Gui.so.5' || echo '✗ libQt5Gui.so.5'
cp /usr/lib/x86_64-linux-gnu/libQt5DBus.so.5 lib/ 2>/dev/null && echo '✓ libQt5DBus.so.5' || echo '✗ libQt5DBus.so.5'
cp /usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5 lib/ 2>/dev/null && echo '✓ libQt5XcbQpa.so.5' || echo '✗ libQt5XcbQpa.so.5'

# Copier les plugins de plateforme
echo 'Copie des plugins Qt5...'
if [ -d '/usr/lib/x86_64-linux-gnu/qt5/plugins/platforms' ]; then
    cp -r /usr/lib/x86_64-linux-gnu/qt5/plugins/platforms plugins/
    echo '✓ Plugins de plateforme copiés'
else
    echo '✗ Plugins de plateforme non trouvés'
fi

# Copier les bibliothèques XCB
echo 'Copie des bibliothèques XCB...'
cp /usr/lib/x86_64-linux-gnu/libxcb.so.1 lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libxcb-*.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libX11.so.6 lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libXext.so.6 lib/ 2>/dev/null

# Bibliothèques système supplémentaires
cp /usr/lib/x86_64-linux-gnu/libicui18n.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libicuuc.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libicudata.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libpcre2-16.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libdouble-conversion.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libglib-2.0.so.* lib/ 2>/dev/null
cp /usr/lib/x86_64-linux-gnu/libmd4c.so.* lib/ 2>/dev/null

echo '=== Déploiement terminé ==='
")

# Créer le script de lancement
file(WRITE ${CMAKE_BINARY_DIR}/run_fonction.sh
"#!/bin/bash
cd \"$(dirname \"$0\")\"
export QT_PLUGIN_PATH=\"./plugins\"
export QT_QPA_PLATFORM_PLUGIN_PATH=\"./plugins/platforms\"
export LD_LIBRARY_PATH=\"./lib:\$LD_LIBRARY_PATH\"
./fonction \"\$@\"
")

# Rendre les scripts exécutables et les exécuter après le build
add_custom_command(TARGET fonction POST_BUILD
    COMMAND chmod +x deploy_qt.sh
    COMMAND chmod +x run_fonction.sh
    COMMAND ./deploy_qt.sh
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Déploiement des bibliothèques Qt5"
)

message(STATUS "Configuration Qt5 pour déploiement autonome")
message(STATUS "Après compilation, utilisez './run_fonction.sh' pour lancer l'application")
