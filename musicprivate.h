#ifndef MUSICPRIVATE_H
#define MUSICPRIVATE_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/


#define MMM_DECLARE_PRIVATE(Class) \
    friend class Class##Private; \
    MMMPrivateInterface<Class, Class##Private> MMM_d;

#define MMM_DECLARE_PUBLIC(Class) \
    friend class Class;

#define MMM_INIT_PRIVATE \
    MMM_d.setPublic(this);

#define MMM_D(Class) Class##Private *const d = MMM_d()
#define MMM_Q(Class) Class *const q = MMM_q()

template <typename PUB>
class MMMPrivate
{
public:
    virtual ~MMMPrivate() { }
    inline void setPublic(PUB* pub) { MMM_q_ptr = pub; }

protected:
    inline PUB *MMM_q() const { return MMM_q_ptr; }

private:
    PUB* MMM_q_ptr;

};

template <typename PUB, typename PVT>
class MMMPrivateInterface
{
    friend class MMMPrivate<PUB>;
public:
    MMMPrivateInterface() { pvt = new PVT; }
    ~MMMPrivateInterface() { delete pvt; }

    inline void setPublic(PUB* pub) { pvt->setPublic(pub); }
    inline PVT *operator()() const { return static_cast<PVT*>(pvt); }

private:
    MMMPrivateInterface(const MMMPrivateInterface&) { }
    MMMPrivateInterface& operator=(const MMMPrivateInterface&) { }
    MMMPrivate<PUB>* pvt;

};


#endif // MUSICPRIVATE_H
