BUILD_DIR = build
CMAKE = cmake

debug:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_BUILD_TYPE=Debug ..
	$(MAKE) -C $(BUILD_DIR)

release:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_BUILD_TYPE=Release ..
	$(MAKE) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
