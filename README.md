# nightowl-stream

C program for authenticating to and retreiving a stream from a camera on specific, old DVR systems.

# What systems are supported?

* Any DVR with firmware DVR04B-53A
* Bunker Hill Security Model #68332
* Swann DVR4 1300
* Various old Night Owl DVR

# Usage

./nightowl-stream \<IP of DVR\> \<channel\>

Channel can be 1-4.

Raw H264-ES video is output to stdio.  Piping it to a file you can play it back
with mplayer or convert it with ffmpeg.
