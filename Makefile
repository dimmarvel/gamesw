BUILD_DIR = build
CMAKE = cmake
COMMANDS_FILE = commands_example.txt
EXE_FILE = sw_battle_test


debug:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_BUILD_TYPE=Debug ..
	$(MAKE) -C $(BUILD_DIR)

release:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_BUILD_TYPE=Release ..
	$(MAKE) -C $(BUILD_DIR)

run:
	./$(BUILD_DIR)/$(EXE_FILE) $(COMMANDS_FILE)

clean:
	rm -rf $(BUILD_DIR)
