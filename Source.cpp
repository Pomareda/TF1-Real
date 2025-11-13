#include "MenuI.h"
using namespace TF1;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MenuI());

	return 0;
}
