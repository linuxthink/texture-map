DEBUG_DIR = Debug

# make only
mp3_make:
	$(MAKE) -C $(DEBUG_DIR) Graphics_MP3

# make and run
mp3:
	$(MAKE) -C $(DEBUG_DIR) Graphics_MP3
	./Debug/Graphics_MP3

# run
run:
	./Debug/Graphics_MP3

# clean
clean:
	$(MAKE) -C $(DEBUG_DIR) clean

.PHONY: mp3_make_only mp3 clean
