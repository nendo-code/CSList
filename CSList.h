#ifndef _CSLIST_H_
#define _CSLIST_H_

#include "CSList_conf.h"

#define CSList_define(type)\
    typedef struct st_CSList_##type CSList_##type;\
    struct st_CSList_##type{\
        void (*Add)(CSList_##type*, type);\
        void (*Clear)(CSList_##type*);\
        type* (*Item)(CSList_##type*, CSList_type_int);\
        void (*CopyTo)(CSList_##type*, type[], CSList_type_int);\
        CSList_type_char (*Contains)(CSList_##type*, type);\
        CSList_type_int (*Count)(CSList_##type*);\
        CSList_type_int (*IndexOf)(CSList_##type*, type);\
        void (*Insert)(CSList_##type*,CSList_type_int, type);\
        CSList_type_char (*Remove)(CSList_##type*, type);\
        void (*RemoveAt)(CSList_##type*, CSList_type_int);\
        /* Regist custom free method.
        *  This method called from Clear(),Remove(),RemoveAt().
        *  arg1 is target of free().
        */\
        void (*customFree)(type*);\
        /* Regist custom compare method.
        *  This method called from Contains(),IndexOf(),Remove().
        *  The return value is as follows.
        *  - value == 0:arg1 and arg2 are equal.
        *  - value > 0:arg1 is larger than arg2.
        *  - value < 0:arg2 is larger than arg1.
        */\
        CSList_type_int (*customCompare)(const type*, const type*);\
        /* Regist custom copy method.
        * This method called from CopyTo().
        * arg1 is destination,arg2 is source.
        */\
        void (*customCopy)(type*, const type*);\
    };\

#define CSList_record(type)\
    typedef struct stCSList_record_##type CSList_record_##type;\
    struct stCSList_record_##type{\
        type value;\
        CSList_record_##type* next;\
    };\

#define CSList_impl_define(type)\
    struct st_CSList_impl_##type{\
        CSList_##type methods;\
        CSList_type_int count;\
        CSList_record_##type* first;\
        CSList_record_##type* last;\
    }typedef CSList_impl_##type;\

#define CSList_prototype(type)\
    static CSList_##type* CSList_new_##type();\
    static void CSList_add_##type(CSList_##type* this, type value);\
    static void CSList_clear_##type(CSList_##type* this);\
    static CSList_type_int CSList_count_##type(CSList_##type* this);\
    static type* CSList_item_##type(CSList_##type* this, CSList_type_int index);\
    static void CSList_copyto_##type(CSList_##type* this, type* array, CSList_type_int arrayIndex);\
    static CSList_type_int CSList_indexof_##type(CSList_##type* this, type item);\
    static CSList_type_char CSList_contains_##type(CSList_##type* this, type item);\
    static void CSList_insert_##type(CSList_##type* this, CSList_type_int index, type item);\
    static void CSList_remove_at_##type(CSList_##type* this, CSList_type_int index);\
    static CSList_type_char CSList_remove_##type(CSList_##type* this, type item);\

#define CSList_foreach(type,itemName,list){\
    type* itemName;\
    CSList_record_##type* cslist_tmp_target;\
    for(cslist_tmp_target = ((CSList_impl_##type*)list)->first; cslist_tmp_target != CSList_null; cslist_tmp_target = cslist_tmp_target->next){\
        itemName = &(cslist_tmp_target->value);\

#define CSList_internal_foreach(type,recordName,list){\
    CSList_record_##type* cslist_tmp_target;\
    CSList_record_##type* recordName;\
    for(cslist_tmp_target = ((CSList_impl_##type*)list)->first; cslist_tmp_target != CSList_null; cslist_tmp_target = cslist_tmp_target->next){\
        recordName = cslist_tmp_target;\

#define CSList_foreach_end }}

#define CSList_functions(type)\
    CSList_onException(type)\
    static CSList_##type* CSList_new_##type(){\
        CSList_impl_##type * ret;\
        ret = (CSList_impl_##type *) CSList_malloc(sizeof(CSList_impl_##type));\
        ret -> methods.Add = CSList_add_##type;\
        ret -> methods.Clear = CSList_clear_##type;\
        ret -> methods.Count = CSList_count_##type;\
        ret -> methods.Item = CSList_item_##type;\
        ret -> methods.CopyTo = CSList_copyto_##type;\
        ret -> methods.IndexOf = CSList_indexof_##type;\
        ret -> methods.Contains = CSList_contains_##type;\
        ret -> methods.Insert = CSList_insert_##type;\
        ret -> methods.RemoveAt = CSList_remove_at_##type;\
        ret -> methods.Remove = CSList_remove_##type;\
        ret -> methods.customFree = CSList_null;\
        ret -> methods.customCompare = CSList_null;\
        ret -> methods.customCopy = CSList_null;\
        ret -> first = CSList_null;\
        ret -> last = CSList_null;\
        ret -> count = 0;\
        return (CSList_##type*)ret;\
    }\
    static void CSList_add_##type(CSList_##type* this, type value){\
        CSList_impl_##type* impl;\
        CSList_record_##type* record;\
        impl = (CSList_impl_##type*)this;\
        record = (CSList_record_##type*)CSList_malloc(sizeof(CSList_record_##type));\
        record->next = CSList_null;\
        record->value = value;\
        if(impl->first == CSList_null){\
            impl->first = impl->last = record;\
        }\
        else{\
            impl->last->next = record;\
            impl->last = record;\
        }\
        impl->count++;\
    }\
    static void CSList_clear_##type(CSList_##type* this){\
        CSList_impl_##type* impl = (CSList_impl_##type*)this;\
        CSList_internal_foreach(type,record,this){\
            CSList_record_##type* tmp = record;\
            if(this->customFree != CSList_null){\
                this->customFree(&(record->value));\
            }\
            CSList_free(tmp);\
        }CSList_foreach_end\
        impl->first = CSList_null;\
        impl->last = CSList_null;\
        impl->count = 0;\
    }\
    static CSList_type_int CSList_count_##type(CSList_##type* this){\
        return ((CSList_impl_##type*)this)->count;\
    }\
    static type* CSList_item_##type(CSList_##type* this,CSList_type_int index){\
        CSList_type_int i = 0;\
        CSList_foreach(type,tmp,this){\
            if(i == index){\
                return tmp;\
            }\
            i++;\
        }CSList_foreach_end\
        return CSList_null;\
    }\
    static void CSList_copyto_##type(CSList_##type* this, type* array, CSList_type_int arrayIndex){\
        CSList_type_int i = 0;\
        if(array == CSList_null){ CSList_onException_##type(CSList_Exceptions_ArgumentNullException); }\
        if(arrayIndex < 0){ CSList_onException_##type(CSList_Exceptions_ArgumentOutOfRangeException); }\
        CSList_foreach(type,tmp,this){\
            if(this->customCopy == CSList_null){\
                array[i+arrayIndex] = *tmp;\
            }else{\
                this->customCopy(&array[i+arrayIndex],tmp);\
            }\
            i++;\
        }CSList_foreach_end\
    }\
    static CSList_type_int CSList_indexof_##type(CSList_##type* this, type item){\
        CSList_type_int index = 0;\
        CSList_foreach(type,tmp,this){\
            if(this->customCompare == CSList_null){\
                if(CSList_memcmp(tmp,&item,sizeof(type)) == 0) {return index;}\
            }else{\
                if(this->customCompare(tmp,&item) == 0) { return index;}\
            }\
            index++;\
        }CSList_foreach_end\
        return -1;\
    }\
    static CSList_type_char CSList_contains_##type(CSList_##type* this, type item){\
        if(this->IndexOf(this,item) == -1){\
            return CSList_false;\
        }else{\
            return CSList_true;\
        }\
    }\
    static void CSList_insert_##type(CSList_##type* this,CSList_type_int index, type item){\
        CSList_record_##type *prevrecord = CSList_null, *nextrecord = CSList_null, *newrecord = CSList_null;\
        CSList_type_int i = 0;\
        CSList_impl_##type* impl = (CSList_impl_##type*)this;\
        if(impl->count < index){ CSList_onException_##type(CSList_Exceptions_ArgumentOutOfRangeException); }\
        if(impl->count == index){ this->Add(this,item); return; }\
        CSList_internal_foreach(type,record,this){\
            if(i==(index-1)){\
                prevrecord = record;\
                break;\
            }\
            i++;\
        }CSList_foreach_end\
        newrecord = (CSList_record_##type*)CSList_malloc(sizeof(CSList_record_##type));\
        newrecord->value = item;\
        if(prevrecord != CSList_null){\
            nextrecord = prevrecord->next;\
            prevrecord->next = newrecord;\
            newrecord->next = nextrecord;\
        } else if(index == 0){\
            newrecord->next = impl->first;\
            impl->first = newrecord;\
        }else{\
            CSList_onException_##type(CSList_Exceptions_InvalidOperationException);\
        }\
        impl->count++;\
    }\
    static void CSList_remove_at_##type(CSList_##type* this,CSList_type_int index){\
        CSList_record_##type *prevrecord = CSList_null, *removerecord = CSList_null;\
        CSList_type_int i = 0;\
        CSList_impl_##type* impl = (CSList_impl_##type*)this;\
        if(impl->count <= index){ CSList_onException_##type(CSList_Exceptions_ArgumentOutOfRangeException); }\
        CSList_internal_foreach(type,record,this){\
            if(i == (index-1)){\
                prevrecord = record;\
                break;\
            }\
            i++;\
        }CSList_foreach_end\
        if(index == 0){\
            removerecord = impl->first;\
            impl->first = removerecord->next;\
            prevrecord = CSList_null;\
        }else{\
            removerecord = prevrecord->next;\
            prevrecord->next = removerecord->next;\
        }\
        if(removerecord == impl->last){\
            impl->last = prevrecord;\
        }\
        if(this->customFree != CSList_null){\
            this->customFree(&(removerecord->value));\
        }\
        CSList_free(removerecord);\
        impl->count--;\
    }\
    static CSList_type_char CSList_remove_##type(CSList_##type* this, type item){\
        CSList_type_int index = this->IndexOf(this,item);\
        if(index == -1){\
            return CSList_false;\
        }\
        this->RemoveAt(this,index);\
        return CSList_true;\
    }\

#define CSList_use(type)\
    CSList_define(type)\
    CSList_record(type)\
    CSList_impl_define(type)\
    CSList_prototype(type)\
    CSList_functions(type)\

#define CSList(type) CSList_##type *
#define CSList_new(type) CSList_new_##type()
#define CSList_delete(list) list->Clear(list);CSList_free(list);

#endif /* _CSLIST_H_ */