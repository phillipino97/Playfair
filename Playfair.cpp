#include <iostream>

using namespace std;

int main() {

  char cipher_key[5][5], choice, double_letter;
  char alphabet[25] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L',
                       'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                       'X', 'Y', 'Z'};
  char repeats[25];
  int num_spaces = 0;
  string key, p, c;

  cout << "Encode (E) or Decode (D): ";
  cin >> choice;

  if(choice == 'E') {

    cout << "Enter the key (One word all caps): ";
    cin >> key;

    for(int i = 0; i < key.length(); i++) {
      if(key[i] == 'J') {
        key[i] = 'I';
      }

      if(key[i] < 74) {
        if(alphabet[key[i]-65] != ' ') {
          alphabet[key[i]-65] = ' ';
        } else {
          key.erase(key.begin()+i);
          i--;
        }
      } else {
        if(alphabet[key[i]-66] != ' ') {
          alphabet[key[i]-66] = ' ';
        } else {
          key.erase(key.begin()+i);
          i--;
        }
      }

    }

    cout << "---------------------" << endl;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
          if(i*5 + j >= key.length()) {
            for(int k = 0; k < 25; k++) {
              if(alphabet[k] != ' ') {
                cipher_key[i][j] = alphabet[k];
                alphabet[k] = ' ';
                break;
              }
            }
          } else {
            cipher_key[i][j] = key[i*5 + j];
          }
          if(j == 0) {
            cout << "| " << cipher_key[i][j];
          } else {
            cout << " | " << cipher_key[i][j];
          }

        }
        cout << " |" << "\n---------------------" << endl;
    }

    cout << "Enter the message to encode: ";
    getline(cin >> ws, p);

    for(int i = 0; i < p.length(); i++) {

      if(p[i] >= 97 && p[i] <= 122) {
        p[i] = p[i]-32;
      }

      if(p[i] == 'J') {
        p[i] = 'I';
      }

      if(p[i] == 32) {
        num_spaces += 1;
      } else if(double_letter == p[i] && (i % 2 != (num_spaces % 2))) {
        p.insert(i, "X");
        i++;
      } else if(i % 2 == (num_spaces % 2)) {
        double_letter = p[i];
      }

      if(i % 2 == (num_spaces % 2) && i == p.length()-1) {
        p += "X";
      }

    }

    //2, 4 & 3, 0
    //2, 0 & 3, 4

    char char1, char2;
    int pos1[2], pos2[2];
    int space_second = 0;
    for(int i = 0; i < p.length(); i+=2) {
      char1 = p[i];
      char2 = p[i+1];

      if(char1 == ' ') {
        c += " ";
        i++;
        char1 = p[i];
        char2 = p[i+1];
      }

      if(char2 == ' ') {
        space_second = 1;
        i++;
        char2 = p[i+1];
      }

      for(int j = 0; j < 5; j++) {
        for(int k = 0; k < 5; k++) {
          if(cipher_key[j][k] == char1) {
            pos1[0] = j;
            pos1[1] = k;
          } else if(cipher_key[j][k] == char2) {
            pos2[0] = j;
            pos2[1] = k;
          }
        }
      }

      if(pos1[0] == pos2[0]) {
        c += cipher_key[pos1[0]][(pos1[1]+1)%5];
        if(space_second) {
          c += " ";
          c += cipher_key[pos2[0]][(pos2[1]+1)%5];
          space_second = 0;
        } else {
          c += cipher_key[pos2[0]][(pos2[1]+1)%5];
        }
      } else if(pos1[1] == pos2[1]) {
        c += cipher_key[(pos1[0]+1)%5][pos1[1]];
        if(space_second) {
          c += " ";
          c += cipher_key[(pos2[0]+1)%5][pos2[1]];
          space_second = 0;
        } else {
          c += cipher_key[(pos2[0]+1)%5][pos2[1]];
        }
      } else {
        c += cipher_key[pos1[0]][pos2[1]];
        if(space_second) {
          c += " ";
          c += cipher_key[pos2[0]][pos1[1]];
          space_second = 0;
        } else {
          c += cipher_key[pos2[0]][pos1[1]];
        }
      }

    }

    cout << "Encoded message: " << c << endl;

  } else if(choice == 'D') {

    cout << "Enter the key (up to 25 letters): ";
    cin >> key;

    for(int i = 0; i < key.length(); i++) {
      if(key[i] == 'J') {
        key[i] = 'I';
      }

      if(key[i] < 74) {
        if(alphabet[key[i]-65] != ' ') {
          alphabet[key[i]-65] = ' ';
        } else {
          key.erase(key.begin()+i);
          i--;
        }
      } else {
        if(alphabet[key[i]-66] != ' ') {
          alphabet[key[i]-66] = ' ';
        } else {
          key.erase(key.begin()+i);
          i--;
        }
      }

    }

    cout << "---------------------" << endl;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
          if(i*5 + j >= key.length()) {
            for(int k = 0; k < 25; k++) {
              if(alphabet[k] != ' ') {
                cipher_key[i][j] = alphabet[k];
                alphabet[k] = ' ';
                break;
              }
            }
          } else {
            cipher_key[i][j] = key[i*5 + j];
          }
          if(j == 0) {
            cout << "| " << cipher_key[i][j];
          } else {
            cout << " | " << cipher_key[i][j];
          }

        }
        cout << " |" << "\n---------------------" << endl;
    }


    cout << "Enter the message to decode: ";
    getline(cin >> ws, p);

    for(int i = 0; i < p.length(); i++) {

      if(p[i] >= 97 && p[i] <= 122) {
        p[i] = p[i]-32;
      }

      if(p[i] == 'J') {
        p[i] = 'I';
      }

    }

    //4, 0 & 3, 3
    //3, 0 & 4, 3

    char char1, char2;
    int pos1[2], pos2[2];
    int space_second = 0;
    for(int i = 0; i < p.length(); i+=2) {
      char1 = p[i];
      char2 = p[i+1];

      if(char1 == ' ') {
        c += " ";
        i++;
        char1 = p[i];
        char2 = p[i+1];
      }

      if(char2 == ' ') {
        space_second = 1;
        i++;
        char2 = p[i+1];
      }

      for(int j = 0; j < 5; j++) {
        for(int k = 0; k < 5; k++) {
          if(cipher_key[j][k] == char1) {
            pos1[0] = j;
            pos1[1] = k;
          } else if(cipher_key[j][k] == char2) {
            pos2[0] = j;
            pos2[1] = k;
          }
        }
      }

      if(pos1[0] == pos2[0]) {
        if(pos1[1]-1 < 0) {
          c += cipher_key[pos1[0]][(pos1[1]+4)];
        } else {
          c += cipher_key[pos1[0]][(pos1[1]-1)];
        }
        if(pos2[1]-1 < 0) {
          if(space_second) {
            c += " ";
            c += cipher_key[pos2[0]][(pos2[1]+4)];
            space_second = 0;
          } else {
            c += cipher_key[pos2[0]][(pos2[1]+4)];
          }
        } else {
          if(space_second) {
            c += " ";
            c += cipher_key[pos2[0]][(pos2[1]-1)];
            space_second = 0;
          } else {
            c += cipher_key[pos2[0]][(pos2[1]-1)];
          }
        }
      } else if(pos1[1] == pos2[1]) {
        if(pos1[0]-1 < 0) {
          c += cipher_key[(pos1[0]+4)][pos1[1]];
        } else {
          c += cipher_key[(pos1[0]-1)][pos1[1]];
        }
        if(pos2[0]-1 < 0) {
          if(space_second) {
            c += " ";
            c += cipher_key[(pos2[0]+4)][pos2[1]];
            space_second = 0;
          } else {
            c += cipher_key[(pos2[0]+4)][pos2[1]];
          }
        } else {
          if(space_second) {
            c += " ";
            c += cipher_key[(pos2[0]-1)][pos2[1]];
            space_second = 0;
          } else {
            c += cipher_key[(pos2[0]-1)][pos2[1]];
          }
        }
      } else {
        c += cipher_key[pos1[0]][pos2[1]];
        if(space_second) {
          c += " ";
          c += cipher_key[pos2[0]][pos1[1]];
          space_second = 0;
        } else {
          c += cipher_key[pos2[0]][pos1[1]];
        }
      }

    }

    cout << "Decoded message: " << c << endl;

  }

  return 1;

}
