#include <iostream>
#include <pandaFramework.h>
#include <pandaSystem.h>
#include <configVariableManager.h>
#include <config_prc.h>
#include <load_prc_file.h>
#include <mouseWatcher.h>
#include <regex>
#include <algorithm>
#include <thread>
#include "main.h"

//#include <ws2tcpip.h>
//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
//#define CPPHTTPLIB_OPENSSL_SUPPORT
//#include "httplib.h"
#include <pgTop.h>
#include <pgEntry.h>
#include "eventHandler.h"
#include "throw_event.h"
#include <pgScrollFrame.h>
#include "httpClient.h"
#include "httpChannel.h"
#include "ramfile.h"

#include <alphaTestAttrib.h>
#include <callbackNode.h>
#include <colorBlendAttrib.h>
#include <depthTestAttrib.h>
#include <directionalLight.h>
#include <DisplayInformation.h>
#include <ambientLight.h>
#include "renderAttrib.h"
#include <texturePool.h>
#include <cardMaker.h>
#include <orthographicLens.h>
#include <cullFaceAttrib.h>
#include <stencilAttrib.h>

PandaFramework framework;
PT(WindowFramework) window;

// print debug to console
void prdbg(const std::string& text) { std::cout << "\nprdebug: " + text + "\n"; }
void prdbg(const std::wstring& text) { std::cout << L"\nprdebug: " + text + L"\n"; }
void prdbg(int number) { std::cout << "\nprdebug: " + std::to_string(number); }
void prdbg(unsigned int number) { std::cout << "\nprdebug: " + std::to_string(number); }
void prdbg(unsigned short int number) { std::cout << "\nprdebug: " + std::to_string(number); }
void prdbg(float number) { std::cout << "\nprdebug: " + std::to_string(number); }
void prdbg(double number) { std::cout << "\nprdebug: " + std::to_string(number); }
void prdbg(size_t number_t) { std::cout << "\nprdebug: " + std::to_string(number_t); }
void prdbg(const LVector3& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y() << " z:" << vec.get_z(); }
void prdbg(const LVector3i& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y() << " z:" << vec.get_z(); }
void prdbg(const LVecBase4& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y() << " z:" << vec.get_z() << " w:" << vec.get_w(); }
void prdbg(const LVecBase2& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y(); }
void prdbg(const LVecBase2i& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y(); }
void prdbg(const LVecBase3& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y() << " z:" << vec.get_z(); }
void prdbg(const LPoint3& vec) { std::cout << "\nprdebug: x:" << vec.get_x() << " y:" << vec.get_y() << " z:" << vec.get_z(); }

void quit_app(const Event* ev, void* data) {
	PT(AsyncTaskManager) task_mgr = AsyncTaskManager::get_global_ptr();
	task_mgr->cleanup();											// remove all tasks
	framework.set_exit_flag();
}

void debug_task(const Event* e, void* data) {															// key: d
  prdbg("debug task done");
}

int main(int argc, char* argv[])   																																										// to run with console window
//int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,	_In_ LPSTR lpCmdLine, _In_ int nShowCmd) {	// to run without console window
{
	framework.open_framework();

	// try to find a resolution which works on lenovo and asuslt
	DisplayInformation* di = framework.get_default_pipe()->get_display_information();
	int disp_mode = di->get_total_display_modes() / 1.1f;  // select one of the supported resolutions
	int width = di->get_display_mode_width(disp_mode);
	int height = di->get_display_mode_height(disp_mode);
	std::string param = "win-size " + std::to_string(width) + " " + std::to_string(height);
	load_prc_file_data("", param);
	load_prc_file_data("", "win-origin -2 -2");

	window = framework.open_window();
	window->enable_keyboard();
	window->setup_trackball();	// enable camera control by mouse

	load_prc_file_data("cpp", "model-cache-dir");						//  disables caching of model files

	// define some keys
	framework.define_key("q", "quit", &quit_app, nullptr);
	framework.define_key("d", "run debug tasks", &debug_task, nullptr);



	framework.main_loop();
	framework.close_framework();
  return 0;
}