#ifndef CDEBUG
#define CDEBUG
class CDebug{
private:
        bool is_debug;
        char *nazwa;
public:
       CDebug(bool value, const char *t_nazwa);
       void operator<<(const char *tekst);
       ~CDebug();
       void Notice(const char *tekst); 
};

#endif 
