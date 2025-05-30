#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

class GLFWwindow;

class Window {
public:
	static int width;
	static int height;
	static GLFWwindow* window; // не лучшее решение делать window публичным
	static int initialize(int width, int height, const char* title);
	static void terminate();

	static void viewport(int x, int y, int width, int height);

	static bool isShouldClose();
	static void Close();
	static void swapBuffers();
	static void swapInterval(int interval);


};

#endif /* WINDOW_WINDOW_H_ */