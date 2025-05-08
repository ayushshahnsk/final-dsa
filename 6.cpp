#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip> // For setw()

using namespace std;

class Flight
{
public:
  vector<vector<int>> am;    // Adjacency matrix
  vector<string> city_index; // City names
  Flight();
  int create();
  void display(int city_count);
};

Flight::Flight()
{
  // Initialize empty adjacency matrix and city list
  am.resize(10, vector<int>(10, 0)); // 10x10 matrix initialized to 0
  city_index.resize(10);
}

int Flight::create()
{
  int city_count = 0, j, si, di, wt;
  char s[10], d[10], c;

  do
  {
    cout << "\nEnter Source City: ";
    cin >> s;
    cout << "Enter Destination City: ";
    cin >> d;

    // Add the source city if it's not in the list
    bool sourceExists = false;
    for (j = 0; j < city_count; j++)
    {
      if (city_index[j] == s)
      {
        sourceExists = true;
        break;
      }
    }
    if (!sourceExists)
    {
      city_index[city_count] = s;
      city_count++;
    }

    // Add the destination city if it's not in the list
    bool destinationExists = false;
    for (j = 0; j < city_count; j++)
    {
      if (city_index[j] == d)
      {
        destinationExists = true;
        break;
      }
    }
    if (!destinationExists)
    {
      city_index[city_count] = d;
      city_count++;
    }

    cout << "Enter Distance From " << s << " And " << d << ": ";
    cin >> wt;

    // Get indices for source and destination cities
    for (j = 0; j < city_count; j++)
    {
      if (city_index[j] == s)
        si = j;
      if (city_index[j] == d)
        di = j;
    }

    // Update the adjacency matrix with the weight for both directions
    am[si][di] = wt; // Distance from source to destination
    am[di][si] = wt; // Distance from destination to source (bidirectional)

    cout << "Do you want to add more cities.....(y/n): ";
    cin >> c;

  } while (c == 'y' || c == 'Y');

  return city_count;
}

void Flight::display(int city_count)
{
  int width = 15; // Set width for aligning the city names and values in the matrix

  cout << "\nDisplaying Adjacency Matrix:\n";
  // Display the city names in the top row
  cout << setw(width) << " "; // For the top-left cell
  for (int i = 0; i < city_count; i++)
  {
    cout << setw(width) << city_index[i];
  }
  cout << "\n";

  // Display the matrix with city names and distances
  for (int i = 0; i < city_count; i++)
  {
    cout << setw(width) << city_index[i]; // City name on the left side of the row
    for (int j = 0; j < city_count; j++)
    {
      cout << setw(width) << am[i][j]; // Distance or 0
    }
    cout << "\n";
  }
}

int main()
{
  Flight f;
  int n, city_count = 0;
  char c;

  do
  {
    cout << "\n*** Flight Main Menu ***";
    cout << "\n1. Create";
    cout << "\n2. Adjacency Matrix";
    cout << "\n3. Exit";
    cout << "\nEnter your choice: ";
    cin >> n;

    switch (n)
    {
    case 1:
      city_count = f.create();
      break;
    case 2:
      f.display(city_count);
      break;
    case 3: // Exit option
      cout << "\nExiting program.\n";
      return 0;
    }

    cout << "\nDo you want to continue in Main Menu....(y/n): ";
    cin >> c;

  } while (c == 'y' || c == 'Y');

  return 0;
}