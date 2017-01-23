//Chapter 5.8
#include "std.lib.facilities"

int main()
try
{
	cout << "Please enter the number of values yo want to sum: ";

	int number_sum{ 0 };
	cin >> number_sum;
	
	cout << "Please enter some integers(press'|' to stop): ";
	
	vector<int> user_inputs;
	for (int x; cin >> x;)
		user_inputs.push_back(x);

	if (number_sum > user_inputs.size()) 
		error("number of values you want to sum exceeds more than integers you enter");

	int sum{ 0 };
	for (int i = 0; i < number_sum; ++i)
		sum += user_inputs[i];

	cout << "The sum of the first 3 numbers (";
	for (int i = 0; i < number_sum; ++i) cout << user_inputs[i] << " ";
	cout << ") is " << sum;


	return 0;
}
catch (exception& e)
{
	cerr << "error : " << e.what() << "\n";
	return 1;
}
