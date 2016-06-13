#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include "list.h"

typedef enum {
	NOTYPE,
	ADV,
	FILM
} videoType;

typedef struct watcher_s watcher_t;
typedef struct watcherList_s watcherList_t;

watcher_t * watcher_new(char * name);
void watcher_free(watcher_t * self);

watcherList_t * watcherList_new(void);
void watcherList_free(watcherList_t * self);
void watcherList_addWatcher(watcherList_t * self, watcher_t * watcher);

typedef struct video_s video_t;
typedef struct videoList_s videoList_t;

video_t * video_new(void);
void video_free(video_t * self);
void video_fill(video_t * self, char * name, videoType type, int length);

videoList_t * videoList_new(void);
void videoList_free(videoList_t * self);

void videoList_addVideo(videoList_t * self, int index, char * name, videoType type, int length);

char * video_getName(const videoList_t * self);
videoType video_getType(const videoList_t * self);
int video_getLength(const videoList_t * self);

void videoList_removeVideo(videoList_t * self, int index);

void videoList_nextVideo(videoList_t * self);

list_t * videoList_getVideoList(const videoList_t * self);
int videoList_getAmount(const videoList_t * self);

void videoList_addWatcher(videoList_t * self, const watcherList_t * watcherList, int watcherListIndex);

void videoList_removeWatcher(videoList_t * self, int index);

int videoList_getWatcherAmount(const videoList_t * self);

#endif // VIDEO_H_INCLUDED
