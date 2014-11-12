#include "PuttyParser.h"

PuttyParser::PuttyParser()
{
    //ctor
}

PuttyParser::~PuttyParser()
{
    //dtor
}

void PuttyParser::parse(string path)
{
    struct dirent *entry;
    DIR *root = opendir(path.c_str());
    if (root != NULL)
    {
//        cout << root->dd_name << endl;

        while ((entry = readdir(root)) != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                string subpath = path;
                subpath += "\\";
                subpath += entry->d_name;
//                cout << subpath << endl;
                parse (subpath);
            }
        }
    }
    else
    {
        if (path.rfind("\\area.txt") != string::npos)
        {
            string slug = path.substr(0,path.rfind("\\area.txt"));
            slug = slug.substr(slug.rfind("\\")+1);
//            cout << "Found area!" << endl;

            Room *room = new Room();
            room->name = bookTitle(slug);

            fstream in(path);
            string line;
            string word;
            string command = "";
            while (getline(in, line))
            {
                istringstream iss(line);
                while (iss)
                {
                    word = getWord((&iss));
                    if (command == "")
                        command = word;
                    else
                    {
                        if (command == "description")
                            room->description = word;
                        else if (command == "contains")
                            room->contents.push_back(word);
                    }

                }
                command = "";
            }
            room->look();
            rooms[slug] = room;
            in.close();
        }
        else
        {
            string slug = path.substr(0,path.rfind(".txt"));
            slug = slug.substr(slug.rfind("\\")+1);
//            cout << "Found thing!" << endl;

            Thing *thing = new Thing();
            thing->filename = slug;

            fstream in(path);
            string line;
            string word;
            string command = "";
            while (getline(in, line))
            {
                istringstream iss(line);
                while (iss)
                {
                    word = getWord((&iss));
                    if (word != "")
                    {
                        if (command == "")
                        {
                            command = word;
                            if (command == "isLocked")
                                thing->isLocked = true;
                            else if (command == "isFree")
                                thing->isFree = true;
                            else if (command == "isReadable")
                                thing->isReadable = true;
                            else if (command == "isAnchored")
                                thing->isAnchored = true;
                            else if (command == "isContainer")
                                thing->isContainer = true;
                        }
                        else
                        {
                            if (command == "keywords")
                                thing->keywords.push_back(word);
                            else if (command == "description")
                                thing->description = word;
                            else if (command == "contains")
                                thing->contents.push_back(word);
                            else if (command == "size")
                                thing->size = atoi(word.c_str());
                            else if (command == "capacity")
                                thing->capacity = atoi(word.c_str());
                        }
                    }
                }
                command = "";
            }
            thing->look();
            things[slug] = thing;
            in.close();
        }
        cout << endl;
    }
}

string PuttyParser::getWord(istringstream *iss)
{
    string word = "";
    bool inQuotes = false;
    bool isEscaping = false;
    char c;
    while (*iss)
    {
        c = iss->get();
        if (isEscaping)
        {
            if (c == '"')
                word += '"';
            else if (c == '\\')
                word += '\\';
            else if (c == 'n')
                word += '\n';
            isEscaping = false;
        }
        else if (c == '\\')
            isEscaping = true;
        else if (c == '"')
            inQuotes ^= true;
        else if (!isDelim(c) || inQuotes)
            word += c;
        else if (word != "")
            break;
    }
    return word;
}

string PuttyParser::bookTitle(string original)
{
    string out = "";
    int nextSpace;

    out += toupper(original[0]);
    for (unsigned int i = 1; i < original.length(); i++)
    {
        if (original[i] == ' ')
        {
            nextSpace = original.find(' ', i+1);
            if (nextSpace == -1)
                nextSpace = original.length();
        }
        if (original[i-1] == ' ' && nextSpace - i > 3)
            out += toupper(original[i]);
        else
            out += original[i];
    }
    return out;
}

bool PuttyParser::isDelim(char c)
{
    vector<char> delims = {':', ' ', ',', static_cast<char>(-1)};
    for (char d : delims)
    {
        if (d == c)
            return true;
    }
    return false;
}
