require 'mkmf'

dir_config('ralleg5')

CFLAGS='-O3'

unless find_header("allegro.h", "/usr/include/allegro5", "/usr/local/include/allegro5")
  raise "Allegro5 includes not found!" 
end

unless find_library("allegro", "al_get_allegro_version", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 library not found!" 
end


unless find_library("allegro_image", "al_init_image_addon", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 image addon library not found!" 
end


create_makefile("ralleg5")

