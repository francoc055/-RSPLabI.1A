#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "posts.h"

ePosts* posts_new()
{
    ePosts* m = (ePosts*) malloc(sizeof(ePosts));
    if(m != NULL)
    {
        m->id = 0;
        *(m->user) = '\0';
        m->like = 0;
        m->dislike = 0;
        m->followers = 0;
    }
    return m;
}
ePosts* posts_newParametros(char* idStr,char* user,char* likeStr, char* dislikeStr, char* followerStr)
{
    ePosts* m = posts_new();
    if(m != NULL)
    {
        if(!(posts_setId(m, atoi(idStr)) &&
        posts_setUser(m, user) &&
        posts_setLike(m, atoi(likeStr)) &&
        posts_setDislike(m, atoi(dislikeStr))&&
        posts_setFollower(m, atoi(followerStr))))
        {
            free(m);
            m = NULL;
        }
    }

	return m;
}

void posts_delete(ePosts* this)
{
    free(this);
}

int posts_setId(ePosts* this,int id)
{
    int ret = 0;

	    if(this != NULL && id >= 1)
	    {
	        this->id = id;
	        ret = 1;
	    }

	return ret;
}
int posts_getId(ePosts* this,int* id)
{
    int ret = 0;
	    if(this != NULL && id != NULL)
	    {
	        *id = this->id;
	        ret = 1;
	    }
	return ret;
}

int posts_setUser(ePosts* this,char* user)
{
    int ret = 0;
	    if(this != NULL && user != NULL && strlen(user) <= 100)
	    {
	        strcpy(this->user, user);
	        this->user[0] = toupper(this->user[0]);
	        ret = 1;
	    }
	return ret;
}
int posts_GetUser(ePosts* this,char* user)
{
    int ret = 0;

	    if(this != NULL && user != NULL)
	    {
	        strcpy(user, this->user);

	        ret = 1;
	    }
	return ret;
}

int posts_setLike(ePosts* this,int like)
{
    int ret = 0;
	    if(this != NULL && like >= 0)
	    {
	        this->like = like;
	        ret = 1;
	    }
	return ret;
}
int posts_getLike(ePosts* this,int* like)
{
    int ret = 0;
	    if(this != NULL && like != NULL)
	    {
	        *like = this->like;
	        ret = 1;
	    }
	return ret;
}


int posts_setDislike(ePosts* this,int dislike)
{
    int ret = 0;
	    if(this != NULL && dislike >= 0)
	    {
	        this->dislike = dislike;
	        ret = 1;
	    }
	return ret;
}
int posts_getDislike(ePosts* this,int* dislike)
{
    int ret = 0;
	    if(this != NULL && dislike != NULL)
	    {
	        *dislike = this->dislike;
	        ret = 1;
	    }
	return ret;
}

int posts_setFollower(ePosts* this,int follower)
{
    int ret = 0;
	    if(this != NULL && follower >= 0)
	    {
	        this->followers = follower;
	        ret = 1;
	    }
	return ret;
}
int posts_getFollower(ePosts* this,int* follower)
{
    int ret = 0;
	    if(this != NULL && follower != NULL)
	    {
	        *follower = this->followers;
	        ret = 1;
	    }
	return ret;
}
