#ifndef CUTEST_ASSERTMACROS_H_INCLUDED
#define CUTEST_ASSERTMACROS_H_INCLUDED

/*
 * ---------------------------------
 * Macros for assertions used in unit tests
 * ---------------------------------
 */
#define CuPass(tc)                            CuAssert_Line((tc), __FILE__, __LINE__, "Passed!", (true))
#define CuFail(tc)                            CuFail_Line  ((tc), __FILE__, __LINE__, "assert failed", "")
#define CuFail_Msg(tc, ms)                    CuAssertTrue_Msg(tc, ms, false)

#define CuAssert(tc, ms, cond)                CuAssert_Line((tc), __FILE__, __LINE__, (ms), (cond))
#define CuAssertTrue(tc, cond)                CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", (cond))
#define CuAssertFalse(tc, cond)               CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", !(cond))
#define CuAssertTrue_Msg(tc, ms, cond)        CuAssert_Line((tc), __FILE__, __LINE__, (ms), (cond))
#define CuAssertFalse_Msg(tc, ms, cond)       CuAssert_Line((tc), __FILE__, __LINE__, (ms), !(cond))

#define CuAssertStrEquals(tc,ex,ac)           CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertStrEquals_Msg(tc,ms,ex,ac)    CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertIntEquals(tc,ex,ac)           CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertIntEquals_Msg(tc,ms,ex,ac)    CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertDblEquals(tc,ex,ac,dl)        CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),(dl))
#define CuAssertDblEquals_Msg(tc,ms,ex,ac,dl) CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),(dl))
#define CuAssertPtrEquals(tc,ex,ac)           CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertPtrEquals_Msg(tc,ms,ex,ac)    CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))

#define CuAssertPtrNotNull(tc,p)        CuAssert_Line((tc),__FILE__,__LINE__,"null pointer unexpected",((p) != NULL))
#define CuAssertPtrNotNullMsg(tc,msg,p) CuAssert_Line((tc),__FILE__,__LINE__,(msg),((p) != NULL))
#define CuAssertPtrNull(tc,p)           CuAssert_Line((tc),__FILE__,__LINE__,"null pointer expected",((p) == NULL))
#define CuAssertPtrNullMsg(tc,msg,p)    CuAssert_Line((tc),__FILE__,__LINE__,(msg),((p) == NULL))

#define CuAssertArrayEquals(tc,ex,ac,elemsize,len)                     CuAssertArrayEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),elemsize,len)
#define CuAssertArrayEquals_Msg(tc,ms,ex,ac,elemsize,len)              CuAssertArrayEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),elemsize,len)
#define CuAssertArrayEqualsStepFunc(tc,func,ac,elemsize,len)           CuAssertArrayEqualsStepFunc_LineMsg((tc),__FILE__,__LINE__,#ac,(func),(ac),elemsize,len)
#define CuAssertArrayEqualsStepFunc_Msg(tc,ms,func,ac,elemsize,len)    CuAssertArrayEqualsStepFunc_LineMsg((tc),__FILE__,__LINE__,(ms),(func),(ac),elemsize,len)
#define CuAssertArrayElementsConstant(tc,ex,ac,elemsize,len)           CuAssertArrayElementsConstant_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),elemsize,len)
#define CuAssertArrayElementsConstant_Msg(tc,ms,ex,ac,elemsize,len)    CuAssertArrayElementsConstant_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),elemsize,len)


#endif // CUTEST_ASSERTMACROS_H_INCLUDED
