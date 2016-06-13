#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "video.h"

struct watcher_s {
	char name[100];
};

watcher_t * watcher_new(char * name) {
	watcher_t * watcherSmp = malloc(sizeof(struct watcher_s));
	strcpy(watcherSmp->name, name);
	return watcherSmp;
}

void watcher_free(watcher_t * self) {
	free(self);
}

struct watcherList_s {
	list_t * watcherList;
};

watcherList_t * watcherList_new(void) {
	watcherList_t * watcherListSmp = malloc(sizeof(struct watcherList_s));
	watcherListSmp->watcherList = list_new();
	return watcherListSmp;
}

void watcherList_free(watcherList_t * self) {
	int amount = list_getSize(self->watcherList);
	for (int i = 0; i < amount; i++) {
		watcher_free((watcher_t *)list_pop_back(self->watcherList));
	}
	list_free(self->watcherList);
	free(self);
}

void watcherList_addWatcher(watcherList_t * self, watcher_t * watcher) {
	list_push_back(self, watcher);
}

// -------------------------------

struct video_s {
	char name[100];
	videoType type;
	int secLength;
};

video_t * video_new(void) {
	video_t * videoSmp = malloc(sizeof(struct video_s));
	strcpy(videoSmp->name, "NoName");
	videoSmp->type = NOTYPE;
	videoSmp->secLength = 0;
	return videoSmp;
}

void video_free(video_t * self) {
	free(self);
}

void video_fill(video_t * self, char * name, videoType type, int length) {
	strcpy(self->name, name);
	self->type = type;
	self->secLength = length;
}

// ------------------------------------------------------

struct videoList_s {
	list_t * videoList;
	int videoAmount;
	int curVideo;
	list_t * activeWatcherList;
	int activeWatcherAmount;
};

videoList_t * videoList_new(void) {
	videoList_t * videoListSmp = malloc(sizeof(struct videoList_s));
	videoListSmp->videoList = list_new();
	videoListSmp->videoAmount = 0;
	videoListSmp->curVideo = 0;
	videoListSmp->activeWatcherList = list_new();
	videoListSmp->activeWatcherAmount = 0;
	return videoListSmp;
}

void videoList_free(videoList_t * self) {
	for (int i = 0; i < self->videoAmount; i++) {
		video_free((video_t *)list_pop_back(self->videoList));
	}
	list_free(self->videoList);
	free(self);
}

static int videoList_indexCorrect(videoList_t * self, int index) {
	return index >= 0 && index <= self->videoAmount;
}


// TASK 1
void videoList_addVideo(videoList_t * self, int index, char * name, videoType type, int length) {
	if (videoList_indexCorrect(self, index)) {
		video_t * addVideo = video_new();
		video_fill(addVideo, name, type, length);
		list_insert(self->videoList, index, addVideo);
		self->videoAmount++;
	}
}

// TASK 2!
char * video_getName(const videoList_t * self) {
	char * line = calloc(100, sizeof(char));
	const video_t * video = (video_t *)list_get(self->videoList, self->curVideo);
	strcpy(line, video->name);
	return line;
}

// TASK 2
videoType video_getType(const videoList_t * self) {
	const video_t * video = (video_t *)list_get(self->videoList, self->curVideo);
	return video->type;
}

// TASK 2
int video_getLength(const videoList_t * self) {
	const video_t * video = (video_t *)list_get(self->videoList, self->curVideo);
	return video->secLength;
}

// TASK 3
void videoList_removeVideo(videoList_t * self, int index) {
	if (videoList_indexCorrect(self, index)) {
		video_free((video_t *)list_remove(self->videoList, index));
		self->videoAmount--;
	}
}

// TASK 4
void videoList_nextVideo(videoList_t * self) {
	if (self->curVideo < self->videoAmount) {
		self->curVideo++;
	}
}

// TASK 5
list_t * videoList_getVideoList(const videoList_t * self) {
	list_t * listToReturn = list_new_copy(self->videoList);
	return listToReturn;
}

// TASK 5
int videoList_getAmount(const videoList_t * self) {
	return self->videoAmount;
}

// -----------------------

static int watcherList_indexCorrect(watcherList_t * self, int index) {
	return index >= 0 && index < list_getSize(self->watcherList);
}

static watcher_t * watcherList_getWatcher(watcherList_t * self, int index) {
	if (watcherList_indexCorrect(self, index)) {
		return (watcher_t *)list_get(self->watcherList, index);
	}
	else {
		return NULL;
	}
}


static int videoList_watcherIndexCorrect(videoList_t * self, int index) {
	return index >= 0 && index < self->activeWatcherAmount;
}


// TASK 6
void videoList_addWatcher(videoList_t * self, const watcherList_t * watcherList, int watcherListIndex) {
	const watcher_t * addWatcher = watcherList_getWatcher(watcherList, watcherListIndex);
	if (addWatcher != NULL) {
		list_push_back(self->activeWatcherList, addWatcher);
	}
}

// TASK 7
void videoList_removeWatcher(videoList_t * self, int index) {
	if (videoList_watcherIndexCorrect(self, index)) {
		list_remove(self->activeWatcherList, index);
	}
}

// TASK 8
int videoList_getWatcherAmount(const videoList_t * self) {
	return self->activeWatcherAmount;
}
