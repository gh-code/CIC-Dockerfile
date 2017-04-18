/**
 * @file   main.cpp
 * @author Gary Huang <gh.nctu+code@gmail.com>
 * @date   December, 2015
 * @brief  CIC Tool docker
 * 
 * CIC Tool docker execution
 */
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

void usage()
{
    cerr << "Usage: ./cic\n\n";
    exit(1);
}

string exec(const char *cmd)
{
    FILE *pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
        {
            try
            {
                result += buffer;
            }
            catch (const bad_alloc&)
            {
                pclose(pipe);
                throw;
            }
        }
    }
    pclose(pipe);
    return result;
}

static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
        return s;
}

string s_getenv(const char *name)
{
    const char *CC_DISPLAY = getenv(name);
    stringstream ss;
    ss << CC_DISPLAY;
    return ss.str();
}

int main(int argc, char *argv[])
{
    //if (argc > 2) usage();
    if (argc > 1) usage();  // for security issue

    string user((argc == 2) ? argv[1] : exec("whoami")); user = rtrim(user);
    string dflags;
    dflags  = " -e DISPLAY="+s_getenv("DISPLAY");
    //dflags += " -v /tmp/.X11-unix:/tmp/.X11-unix";
    dflags += " --add-host=lscic3:140.126.24.16";
    dflags += " --add-host=lsntu3:140.112.20.56";
    dflags += " --add-host=lsncu3:140.115.71.53";
    dflags += " --add-host=lsnctu:140.113.202.151";
    dflags += " --add-host=lsnchu3:140.120.90.45";
    dflags += " --add-host=lsncku3:140.116.216.91";
    dflags += " --add-host=synology_nas:192.168.1.10";
    string cmd("docker run -it --rm --privileged=true "+dflags+" --env CIC_USER="+user+" cic");

    // execute command as root
    setuid(0);
    system(cmd.c_str());

    return 0;
}
