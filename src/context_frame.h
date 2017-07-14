#ifndef HIENA_CONTEXT_FRAME_H
#define HIENA_CONTEXT_FRAME_H


struct context_frame {
        char placeholder[32];
};

struct context_frame *context_frame_init();

int context_frame_cleanup( struct context_frame * );


#endif /* !HIENA_CONTEXT_FRAME_H */