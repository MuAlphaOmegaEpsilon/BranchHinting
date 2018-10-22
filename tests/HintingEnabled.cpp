#include <BranchHinting.hpp>
#include <cstdlib> // rand () function
#include <cstdio> // printf () function
#include <ctime> // access time to enable dynamic random generation of rand ()

/// A bool function that most of the time returns "true"
bool mostlyTrue () 
{
	int random = rand () % 100;
	return (random < 90);
}

/// A bool function that most of the time returns "false"
bool mostlyFalse () 
{
	return !mostlyTrue ();
}

void foo_one ()
{
	printf ("1\n");
}
void foo_two ()
{
	printf ("2\n");
}
void foo_three ()
{
	printf ("3\n");
}
void foo_four ()
{
	printf ("4\n");
}

int main ()
{
	srand (time (nullptr));

    bool almostAlwaysTrue = mostlyTrue ();
    bool almostAlwaysFalse = mostlyFalse ();
    
    if (LIKELY (almostAlwaysTrue))
        foo_one ();
    else
        foo_two ();

    unlikely_if (almostAlwaysFalse)
        foo_three ();
    else likely_if (almostAlwaysTrue)
        foo_four ();
        
    return 0;
}