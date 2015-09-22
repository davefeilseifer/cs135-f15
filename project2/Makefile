RCMD_DIR = robot_command
all: project_code
.PHONY: project_code

project_code:
	$(MAKE) -C $(RCMD_DIR)

clean:
	$(MAKE) -C $(RCMD_DIR) clean
	rm -rf $(RCMD_DIR)/bin


