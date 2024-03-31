#pragma once
#include <iostream>

int main(int argc, char** argv);

namespace wizm {
	class core_application {

	public:
		core_application();
		~core_application();


	private:
		friend int ::main(int argc, char** argv);

	};
}
