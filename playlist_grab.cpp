#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <vector>
//#include <curl/curl.h>  //why won't it recognize it?

/*NOTES:
yt-dlp -l(list of videos) --no-playlist --max-downloads NUMBER -x(audio only) --audio-format FORMAT

Post-Processing Options man page
Destination?
Man page: {
    Set --default-search "ytsearch" (or run  yt-dlp "ytsearch:-x" ) to search YouTube

    # Save all videos under YouTube directory in your home directory
    -o ~/YouTube/%(title)s.%(ext)s
}

Requires ffmpeg and ffprobe and yt-dlp and curl and curlpp and libcurl
*/

using namespace std;



int main()
{
    vector<string> url_list{"https://www.youtube.com/watch?v=2yJgwwDcgV8"};

    
    int status;
    pid_t pid, wpid;

    pid = fork();
    if (pid == 0) {
        //Child process
        cout << "Successfully forked\n";
        //Download song with yt-dlp
        if (execlp("yt-dlp", "yt-dlp", "-x", "https://www.youtube.com/watch?v=2yJgwwDcgV8", NULL) == -1) {
            cout << "\nyt-dlp call failed\n";
        }
        exit(EXIT_FAILURE);
    } else {
        //Parent process
        do {
            // wait for child process id to change when its terminated
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }


    return 0;
}