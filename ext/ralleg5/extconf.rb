require 'mkmf'

dir_config('ralleg5')

CFLAGS='-O3'

ALLEGRO5_LIBDIR = ["/usr/lib", "/usr/local/lib"]
ALLEGRO5_INCDIR = ["/usr/include/allegro5", "/usr/local/include/allegro5"] 


unless find_header("allegro.h", "/usr/include/allegro5", "/usr/local/include/allegro5")
  raise "Allegro5 includes not found!" 
end

unless find_header("allegro_image.h", "/usr/include/allegro5", "/usr/local/include/allegro5")
  raise "Allegro5 image addon includes not found!" 
end


unless find_library("allegro", "al_get_allegro_version", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 library not found!" 
end


unless find_library("allegro_image", "al_init_image_addon", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 image addon library not found!" 
end

unless find_library("allegro_primitives", "al_init_primitives_addon", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 image addon library not found!" 
end

unless find_library("allegro_audio", "al_install_audio", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 audio library not found!" 
end

unless find_library("allegro_acodec", "al_init_acodec_addon", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 acodec library not found!" 
end

unless find_library("allegro_font", "al_init_font_addon", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 font addon library not found!" 
end

unless find_library("allegro_ttf", "al_init_ttf_addon", "/usr/lib", "/usr/local/lib")
  raise "Allegro5 ttf addon library not found!" 
end

if enable_config("allegro_dialog")
  if find_library("allegro_dialog", "al_create_native_file_dialog",
        "/usr/lib", "/usr/local/lib")
          
  unless $defs.include? "-DRALLEG5_WITH_DIALOG"
      $defs.push("-DRALLEG5_WITH_DIALOG")
  end   
     
  else       
    warn "Allegro5 dialog addon library not found or not compiling! Dialogs will be disabled in this build!"
  end

end




=begin
Allegro consists of the following libraries: 
liballegro_acodec
liballegro_audio
liballegro_color
liballegro_dialog
liballegro_font
liballegro_image
liballegro_main
liballegro_memfile
liballegro_physfs
liballegro_primitives
liballegro
liballegro_ttf
=end

create_header
create_makefile("ralleg5")


