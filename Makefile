# ===== Compiler =====
CC = gcc

# ===== Flags =====
CFLAGS = -Wall -Wextra -Icore
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

# ===== Folders =====
CORE = core/engine.c
CLI = cli/main_cli.c
GUI = gui/main_gui.c

# ===== Outputs =====
CLI_OUT = CustomShell_CLI
GUI_OUT = CustomShell_GUI

# =====================
# Default build
# =====================
all: cli gui

# =====================
# CLI version (Path A)
# =====================
cli: $(CLI) $(CORE)
	$(CC) $(CFLAGS) $(CLI) $(CORE) -o $(CLI_OUT)

# =====================
# GUI version (Path B)
# =====================
gui: $(GUI) $(CORE)
	$(CC) $(CFLAGS) $(GUI) $(CORE) -o $(GUI_OUT) $(GTK_FLAGS)

# =====================
# Run CLI
# =====================
run-cli: cli
	./$(CLI_OUT)

# =====================
# Run GUI
# =====================
run-gui: gui
	./$(GUI_OUT)

# =====================
# Clean build files
# =====================
clean:
	rm -f $(CLI_OUT) $(GUI_OUT)

# =====================
# Rebuild everything
# =====================
rebuild: clean all
