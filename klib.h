#ifndef _KLIB_INCLUDED
#define _KLIB_INCLUDED

namespace klib
  {
    char* itoa(int value,int base,char* result);          
    void* memset(void* ptr,int value,size_t num);
    
    template <typename T>
    void swap(T &a, T &b)
      {
        T tmp = a;
        a = b;
        b = tmp;   
      }      
   


   template <typename T>
    void sort(T  &data,size_t start ,size_t end)
      {
        if(end - start < 2 )
          {
            //An array of 1 is already sorted, don't do anything  
            return;
          } 
        
        if( end-start < 8 )
          {
            //insertion sort when the array is small
            auto max=data[start];
            size_t maxkey=0;
            for(size_t i=start;i < end; i++)
              {
                if(max < data[i] )
                  {
                    max = data[i];
                    maxkey=i;
                  }
               }

                klib::swap(data[maxkey],data[end-1]);
               
                klib::sort(data,start,--end);
            return;
          }
       
   
         //otherwise this quicksort...
         auto pivot = data[end-1];

         size_t j = start;

         for(size_t i=start; i < end; i++)
           {
             if(data[i] < pivot)
               {
                 klib::swap(data[i],data[j]);
                 j++;                                    
               }             

           } 
         
             klib::swap(data[j],data[end-1]);

         if( j > 1)
           {  
             klib::sort(data,start,--j);
           }  
         if(j<end)
           {
             klib::sort(data,++j,end);
           }  
         return; 
      }        
/*
    template <typename T>
    void sort(T  &data,size_t start ,size_t end)
      {
        if( start==end )
          {
            return;
          }
    
         auto pivot = data[end/2];
         size_t j = start;
    
         for(size_t i=0; i < end; i++)
           {
             if(data[i] < pivot)
               {
                 klib::swap(data[i],data[j]);
                 j++;                                    
               }             
           } 
         klib::swap(data[j],data[end]);
    
         //klib::sort(data,start,--j);
         //klib::sort(data,++j,end);
    
         return; 
      }        
*/
  }          

#endif

