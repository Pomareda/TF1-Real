#include "MenuForm.h"
using namespace TF1;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MenuForm());

	return 0;
}
