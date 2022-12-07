#ifndef POSTS_H_INCLUDED
#define POSTS_H_INCLUDED

typedef struct{
int id;
char user[50];
int like;
int dislike;
int followers;
}ePosts;


#endif // POSTS_H_INCLUDED

ePosts* posts_new();
ePosts* posts_newParametros(char* idStr,char* user,char* likeStr, char* dislikeStr, char* followerStr);
void posts_delete(ePosts* this);

int posts_setId(ePosts* this,int id);
int posts_getId(ePosts* this,int* id);
int posts_setUser(ePosts* this,char* user);
int posts_GetUser(ePosts* this,char* user);
int posts_setLike(ePosts* this,int like);
int posts_getLike(ePosts* this,int* like);
int posts_setDislike(ePosts* this,int dislike);
int posts_getDislike(ePosts* this,int* dislike);
int posts_setFollower(ePosts* this,int follower);
int posts_getFollower(ePosts* this,int* follower);
