#ifndef __TASK_LIA__
#define __TASK_LIA__


namespace lia
{
    class Task
    {
        public:
            virtual void Start();
            virtual bool Execute();
            virtual void Stop();
    };
}

#endif //__TASK_LIA__