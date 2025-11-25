#include "Menu_Interactivo.h"

using namespace TF1;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Menu_Interactivo());

	return 0;
}
