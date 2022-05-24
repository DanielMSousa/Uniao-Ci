#define QTDThread 10
pthread_t pthread[QTDThread]

for(long i = 0; i < QTDThread; i++){
    pthread_create(&pthread[i], NULL, vsdf, (void*)i)
}
for(long i = 0; i < QTDThread; i++){
    pthread_join(&pthread[i], NULL)
}



void* jshdf (void p){
    long idx = (long) p;
}