CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../ImageReader -I../mvcutil -I/usr/local/include -I.

# >>> FOR LINUX, uncomment next few lines; comment out the MAC ones.
C_FLAGS = -fPIC -g -c $(INC) -DGL_GLEXT_PROTOTYPES
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL
MAKE = make
# >>> FOR MAC, uncomment next few lines; comment out previous linux ones.
# C_FLAGS = -fPIC -g -c $(INC) -DGLFW_INCLUDE_GLEXT -DGLFW_INCLUDE_GLCOREARB -DGL_SILENCE_DEPRECATION
# GL_LIBRARIES = -L/usr/local/lib -lglfw -framework OpenGL
# MAKE = make -f MakefileMac
# >>> END: FOR LINUX - FOR MAC

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so

OBJS = main.o Tree.o House.o Mountain.o

main: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o main $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++ ../cryphutil/AffVector.h ../cryphutil/AffVector.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; $(MAKE))

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; $(MAKE))

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; $(MAKE))

main.o: main.c++
	$(CPP) $(C_FLAGS) main.c++
Tree.o: Tree.h Tree.c++
	$(CPP) $(C_FLAGS) Tree.c++
House.o: House.h House.c++
	$(CPP) $(C_FLAGS) House.c++
Mountain.o: Mountain.h Mountain.c++
	$(CPP) $(C_FLAGS) Mountain.c++
