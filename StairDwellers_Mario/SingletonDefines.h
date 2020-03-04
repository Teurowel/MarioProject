#ifndef _SINGLETON_DEFINES_H_
#define _SINGLETON_DEFINES_H_

//Declare constructor, destroctor, copy constructor, assignment operator
#define	NO_COPY(CLASSNAME)							\
		private:									\
		CLASSNAME();								\
		~CLASSNAME() {}								\
		CLASSNAME(const CLASSNAME&) {}				\
		CLASSNAME& operator = (const CLASSNAME&) {}	

//Use DECLARE_SINGLETON in class declaration in header file
#define DECLARE_SINGLETON(CLASSNAME)				\
		NO_COPY(CLASSNAME)							\
		private:									\
			static CLASSNAME* pInst;				\
		public:										\
			static CLASSNAME* GetInst();			\
			void DestroyInst();				

//Use IMPLEMENT_SINGLETON in cpp file to implement singleton
#define	IMPLEMENT_SINGLETON(CLASSNAME)				\
		CLASSNAME* CLASSNAME::pInst = nullptr;		\
		CLASSNAME* CLASSNAME::GetInst()				\
		{											\
			if(pInst == nullptr)					\
				pInst = new CLASSNAME;				\
			return pInst;							\
		}											\
		void CLASSNAME::DestroyInst()				\
		{											\
			if(pInst != nullptr)					\
			{										\
				delete pInst;						\
				pInst = nullptr;					\
			}										\
		}	

#endif