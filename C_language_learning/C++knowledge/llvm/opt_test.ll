; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx26.0.0"

%"class.std::__1::basic_ostream" = type { ptr, %"class.std::__1::basic_ios.base" }
%"class.std::__1::basic_ios.base" = type <{ %"class.std::__1::ios_base", ptr, %"struct.std::__1::_SentinelValueFill" }>
%"class.std::__1::ios_base" = type { ptr, i32, i64, i64, i32, i32, ptr, ptr, ptr, ptr, i64, i64, ptr, i64, i64, ptr, i64, i64 }
%"struct.std::__1::_SentinelValueFill" = type { i32 }
%"class.std::__1::locale::id" = type <{ %"struct.std::__1::once_flag", i32, [4 x i8] }>
%"struct.std::__1::once_flag" = type { i64 }
%"class.std::__1::locale" = type { ptr }
%"class.std::__1::basic_ostream<char>::sentry" = type { i8, ptr }
%"class.std::__1::basic_string" = type { %struct.anon }
%struct.anon = type { %"union.std::__1::basic_string<char>::__rep" }
%"union.std::__1::basic_string<char>::__rep" = type { %"struct.std::__1::basic_string<char>::__long" }
%"struct.std::__1::basic_string<char>::__long" = type { ptr, i64, i64 }

@_ZNSt3__14coutE = external global %"class.std::__1::basic_ostream", align 8
@.str = private unnamed_addr constant [15 x i8] c"The square of \00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c" is \00", align 1
@.str.2 = private unnamed_addr constant [13 x i8] c"basic_string\00", align 1
@_ZTISt12length_error = external constant ptr
@_ZTVSt12length_error = external unnamed_addr constant { [5 x ptr] }, align 8
@_ZNSt3__15ctypeIcE2idE = external global %"class.std::__1::locale::id", align 8

; Function Attrs: mustprogress nofree norecurse nosync nounwind ssp willreturn memory(none) uwtable(sync)
define i32 @_Z6squarei(i32 noundef %0) local_unnamed_addr #0 {
  %2 = mul nsw i32 %0, %0
  ret i32 %2
}

; Function Attrs: mustprogress norecurse ssp uwtable(sync)
define noundef i32 @main() local_unnamed_addr #1 personality ptr @__gxx_personality_v0 {
  %1 = alloca %"class.std::__1::locale", align 8
  %2 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__124__put_character_sequenceB9nqe210106IcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(ptr noundef nonnull align 8 dereferenceable(8) @_ZNSt3__14coutE, ptr noundef nonnull @.str, i64 noundef 14)
  %3 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi(ptr noundef nonnull %2, i32 noundef 5)
  %4 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__124__put_character_sequenceB9nqe210106IcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(ptr noundef nonnull align 8 dereferenceable(8) %3, ptr noundef nonnull @.str.1, i64 noundef 4)
  %5 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi(ptr noundef nonnull %4, i32 noundef 25)
  %6 = load ptr, ptr %5, align 8, !tbaa !6
  %7 = getelementptr i8, ptr %6, i64 -24
  %8 = load i64, ptr %7, align 8
  %9 = getelementptr inbounds i8, ptr %5, i64 %8
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %1) #14
  call void @_ZNKSt3__18ios_base6getlocEv(ptr dead_on_unwind nonnull writable sret(%"class.std::__1::locale") align 8 %1, ptr noundef nonnull %9)
  %10 = invoke noundef nonnull align 8 dereferenceable(25) ptr @_ZNKSt3__16locale9use_facetERNS0_2idE(ptr noundef nonnull align 8 dereferenceable(8) %1, ptr noundef nonnull align 8 dereferenceable(12) @_ZNSt3__15ctypeIcE2idE)
          to label %11 unwind label %16

11:                                               ; preds = %0
  %12 = load ptr, ptr %10, align 8, !tbaa !6
  %13 = getelementptr inbounds nuw i8, ptr %12, i64 56
  %14 = load ptr, ptr %13, align 8
  %15 = invoke signext i8 %14(ptr noundef nonnull %10, i8 noundef signext 10)
          to label %19 unwind label %16

16:                                               ; preds = %11, %0
  %17 = landingpad { ptr, i32 }
          cleanup
  %18 = call ptr @_ZNSt3__16localeD1Ev(ptr noundef nonnull %1) #14
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %1) #14
  resume { ptr, i32 } %17

19:                                               ; preds = %11
  %20 = call ptr @_ZNSt3__16localeD1Ev(ptr noundef nonnull %1) #14
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %1) #14
  %21 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc(ptr noundef nonnull align 8 dereferenceable(8) %5, i8 noundef signext %15)
  %22 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv(ptr noundef nonnull align 8 dereferenceable(8) %5)
  ret i32 0
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #2

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi(ptr noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #2

; Function Attrs: mustprogress ssp uwtable(sync)
define linkonce_odr hidden noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__124__put_character_sequenceB9nqe210106IcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(ptr noundef nonnull align 8 dereferenceable(8) %0, ptr noundef %1, i64 noundef %2) local_unnamed_addr #4 personality ptr @__gxx_personality_v0 {
  %4 = alloca %"class.std::__1::locale", align 8
  %5 = alloca %"class.std::__1::basic_ostream<char>::sentry", align 8
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %5) #14
  %6 = invoke ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(ptr noundef nonnull %5, ptr noundef nonnull align 8 dereferenceable(8) %0)
          to label %7 unwind label %55

7:                                                ; preds = %3
  %8 = load i8, ptr %5, align 8, !tbaa !9, !range !15, !noundef !16
  %9 = trunc nuw i8 %8 to i1
  br i1 %9, label %10, label %61

10:                                               ; preds = %7
  %11 = load ptr, ptr %0, align 8, !tbaa !6
  %12 = getelementptr i8, ptr %11, i64 -24
  %13 = load i64, ptr %12, align 8
  %14 = getelementptr inbounds i8, ptr %0, i64 %13
  %15 = getelementptr inbounds nuw i8, ptr %14, i64 40
  %16 = load ptr, ptr %15, align 8, !tbaa !17
  %17 = getelementptr inbounds nuw i8, ptr %14, i64 8
  %18 = load i32, ptr %17, align 8, !tbaa !24
  %19 = getelementptr inbounds nuw i8, ptr %14, i64 144
  %20 = load i32, ptr %19, align 1, !tbaa !25
  %21 = icmp eq i32 %20, -1
  br i1 %21, label %22, label %36

22:                                               ; preds = %10
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %4) #14
  invoke void @_ZNKSt3__18ios_base6getlocEv(ptr dead_on_unwind nonnull writable sret(%"class.std::__1::locale") align 8 %4, ptr noundef nonnull %14)
          to label %23 unwind label %59

23:                                               ; preds = %22
  %24 = invoke noundef nonnull align 8 dereferenceable(25) ptr @_ZNKSt3__16locale9use_facetERNS0_2idE(ptr noundef nonnull align 8 dereferenceable(8) %4, ptr noundef nonnull align 8 dereferenceable(12) @_ZNSt3__15ctypeIcE2idE)
          to label %25 unwind label %30

25:                                               ; preds = %23
  %26 = load ptr, ptr %24, align 8, !tbaa !6
  %27 = getelementptr inbounds nuw i8, ptr %26, i64 56
  %28 = load ptr, ptr %27, align 8
  %29 = invoke signext i8 %28(ptr noundef nonnull %24, i8 noundef signext 32)
          to label %33 unwind label %30

30:                                               ; preds = %25, %23
  %31 = landingpad { ptr, i32 }
          catch ptr null
  %32 = call ptr @_ZNSt3__16localeD1Ev(ptr noundef nonnull %4) #14
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #14
  br label %63

33:                                               ; preds = %25
  %34 = call ptr @_ZNSt3__16localeD1Ev(ptr noundef nonnull %4) #14
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #14
  %35 = sext i8 %29 to i32
  store i32 %35, ptr %19, align 1, !tbaa !25
  br label %36

36:                                               ; preds = %33, %10
  %37 = phi i32 [ %35, %33 ], [ %20, %10 ]
  %38 = trunc i32 %37 to i8
  %39 = and i32 %18, 176
  %40 = icmp eq i32 %39, 32
  %41 = getelementptr inbounds nuw i8, ptr %1, i64 %2
  %42 = select i1 %40, ptr %41, ptr %1
  %43 = ptrtoint ptr %16 to i64
  %44 = invoke i64 @_ZNSt3__116__pad_and_outputB9nqe210106IcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_(i64 %43, ptr noundef %1, ptr noundef %42, ptr noundef %41, ptr noundef nonnull align 8 dereferenceable(136) %14, i8 noundef signext %38)
          to label %45 unwind label %59

45:                                               ; preds = %36
  %46 = icmp eq i64 %44, 0
  br i1 %46, label %47, label %61

47:                                               ; preds = %45
  %48 = load ptr, ptr %0, align 8, !tbaa !6
  %49 = getelementptr i8, ptr %48, i64 -24
  %50 = load i64, ptr %49, align 8
  %51 = getelementptr inbounds i8, ptr %0, i64 %50
  %52 = getelementptr inbounds nuw i8, ptr %51, i64 32
  %53 = load i32, ptr %52, align 8, !tbaa !27
  %54 = or i32 %53, 5
  invoke void @_ZNSt3__18ios_base5clearEj(ptr noundef nonnull %51, i32 noundef %54)
          to label %61 unwind label %57

55:                                               ; preds = %3
  %56 = landingpad { ptr, i32 }
          catch ptr null
  br label %66

57:                                               ; preds = %47
  %58 = landingpad { ptr, i32 }
          catch ptr null
  br label %63

59:                                               ; preds = %22, %36
  %60 = landingpad { ptr, i32 }
          catch ptr null
  br label %63

61:                                               ; preds = %47, %45, %7
  %62 = call ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(ptr noundef nonnull %5) #14
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %5) #14
  br label %75

63:                                               ; preds = %59, %30, %57
  %64 = phi { ptr, i32 } [ %58, %57 ], [ %60, %59 ], [ %31, %30 ]
  %65 = call ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(ptr noundef nonnull %5) #14
  br label %66

66:                                               ; preds = %63, %55
  %67 = phi { ptr, i32 } [ %64, %63 ], [ %56, %55 ]
  %68 = extractvalue { ptr, i32 } %67, 0
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %5) #14
  %69 = call ptr @__cxa_begin_catch(ptr %68) #14
  %70 = load ptr, ptr %0, align 8, !tbaa !6
  %71 = getelementptr i8, ptr %70, i64 -24
  %72 = load i64, ptr %71, align 8
  %73 = getelementptr inbounds i8, ptr %0, i64 %72
  invoke void @_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv(ptr noundef nonnull %73)
          to label %74 unwind label %76

74:                                               ; preds = %66
  call void @__cxa_end_catch()
  br label %75

75:                                               ; preds = %74, %61
  ret ptr %0

76:                                               ; preds = %66
  %77 = landingpad { ptr, i32 }
          cleanup
  invoke void @__cxa_end_catch()
          to label %78 unwind label %79

78:                                               ; preds = %76
  resume { ptr, i32 } %77

79:                                               ; preds = %76
  %80 = landingpad { ptr, i32 }
          catch ptr null
  %81 = extractvalue { ptr, i32 } %80, 0
  call void @__clang_call_terminate(ptr %81) #15
  unreachable
}

declare ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(ptr noundef returned, ptr noundef nonnull align 8 dereferenceable(8)) unnamed_addr #3

declare i32 @__gxx_personality_v0(...)

; Function Attrs: mustprogress ssp uwtable(sync)
define linkonce_odr hidden i64 @_ZNSt3__116__pad_and_outputB9nqe210106IcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_(i64 %0, ptr noundef %1, ptr noundef %2, ptr noundef %3, ptr noundef nonnull align 8 dereferenceable(136) %4, i8 noundef signext %5) local_unnamed_addr #4 personality ptr @__gxx_personality_v0 {
  %7 = alloca %"class.std::__1::basic_string", align 8
  %8 = inttoptr i64 %0 to ptr
  %9 = icmp eq i64 %0, 0
  br i1 %9, label %81, label %10

10:                                               ; preds = %6
  %11 = ptrtoint ptr %3 to i64
  %12 = ptrtoint ptr %1 to i64
  %13 = sub i64 %11, %12
  %14 = getelementptr inbounds nuw i8, ptr %4, i64 24
  %15 = load i64, ptr %14, align 8, !tbaa !28
  %16 = icmp sgt i64 %15, %13
  %17 = sub nsw i64 %15, %13
  %18 = ptrtoint ptr %2 to i64
  %19 = sub i64 %18, %12
  %20 = icmp sgt i64 %19, 0
  br i1 %20, label %21, label %27

21:                                               ; preds = %10
  %22 = load ptr, ptr %8, align 8, !tbaa !6
  %23 = getelementptr inbounds nuw i8, ptr %22, i64 96
  %24 = load ptr, ptr %23, align 8
  %25 = tail call i64 %24(ptr noundef nonnull %8, ptr noundef %1, i64 noundef %19)
  %26 = icmp eq i64 %25, %19
  br i1 %26, label %27, label %81

27:                                               ; preds = %21, %10
  br i1 %16, label %28, label %71

28:                                               ; preds = %27
  call void @llvm.lifetime.start.p0(i64 24, ptr nonnull %7) #14
  %29 = icmp samesign ugt i64 %17, 9223372036854775798
  br i1 %29, label %30, label %31

30:                                               ; preds = %28
  tail call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE20__throw_length_errorB9nqe210106Ev() #16
  unreachable

31:                                               ; preds = %28
  %32 = icmp samesign ult i64 %17, 23
  br i1 %32, label %42, label %33

33:                                               ; preds = %31
  %34 = or i64 %17, 7
  %35 = icmp eq i64 %34, 23
  %36 = add nuw nsw i64 %34, 1
  %37 = select i1 %35, i64 25, i64 %36
  %38 = tail call noalias nonnull ptr @_Znwm(i64 noundef %37) #17
  store ptr %38, ptr %7, align 8, !tbaa !29
  %39 = getelementptr inbounds nuw i8, ptr %7, i64 16
  %40 = or disjoint i64 %37, -9223372036854775808
  store i64 %40, ptr %39, align 8
  %41 = getelementptr inbounds nuw i8, ptr %7, i64 8
  store i64 %17, ptr %41, align 8, !tbaa !29
  br label %45

42:                                               ; preds = %31
  %43 = trunc nuw nsw i64 %17 to i8
  %44 = getelementptr inbounds nuw i8, ptr %7, i64 23
  store i8 %43, ptr %44, align 1
  br label %45

45:                                               ; preds = %33, %42
  %46 = phi ptr [ %38, %33 ], [ %7, %42 ]
  call void @llvm.memset.p0.i64(ptr nonnull align 1 %46, i8 %5, i64 %17, i1 false), !tbaa !29
  %47 = getelementptr inbounds nuw i8, ptr %46, i64 %17
  store i8 0, ptr %47, align 1, !tbaa !29
  %48 = getelementptr inbounds nuw i8, ptr %7, i64 23
  %49 = load i8, ptr %48, align 1
  %50 = icmp slt i8 %49, 0
  %51 = load ptr, ptr %7, align 8
  %52 = select i1 %50, ptr %51, ptr %7
  %53 = load ptr, ptr %8, align 8, !tbaa !6
  %54 = getelementptr inbounds nuw i8, ptr %53, i64 96
  %55 = load ptr, ptr %54, align 8
  %56 = invoke i64 %55(ptr noundef nonnull %8, ptr noundef %52, i64 noundef %17)
          to label %57 unwind label %64

57:                                               ; preds = %45
  %58 = icmp eq i64 %56, %17
  %59 = load i8, ptr %48, align 1
  %60 = icmp slt i8 %59, 0
  br i1 %60, label %61, label %63

61:                                               ; preds = %57
  %62 = load ptr, ptr %7, align 8, !tbaa !29
  call void @_ZdlPv(ptr noundef %62) #18
  br label %63

63:                                               ; preds = %57, %61
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %7) #14
  br i1 %58, label %71, label %81

64:                                               ; preds = %45
  %65 = landingpad { ptr, i32 }
          cleanup
  %66 = load i8, ptr %48, align 1
  %67 = icmp slt i8 %66, 0
  br i1 %67, label %68, label %70

68:                                               ; preds = %64
  %69 = load ptr, ptr %7, align 8, !tbaa !29
  call void @_ZdlPv(ptr noundef %69) #18
  br label %70

70:                                               ; preds = %64, %68
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %7) #14
  resume { ptr, i32 } %65

71:                                               ; preds = %63, %27
  %72 = sub i64 %11, %18
  %73 = icmp sgt i64 %72, 0
  br i1 %73, label %74, label %80

74:                                               ; preds = %71
  %75 = load ptr, ptr %8, align 8, !tbaa !6
  %76 = getelementptr inbounds nuw i8, ptr %75, i64 96
  %77 = load ptr, ptr %76, align 8
  %78 = call i64 %77(ptr noundef nonnull %8, ptr noundef %2, i64 noundef %72)
  %79 = icmp eq i64 %78, %72
  br i1 %79, label %80, label %81

80:                                               ; preds = %74, %71
  store i64 0, ptr %14, align 8, !tbaa !28
  br label %81

81:                                               ; preds = %80, %63, %21, %74, %6
  %82 = phi i64 [ 0, %6 ], [ %0, %80 ], [ 0, %63 ], [ 0, %21 ], [ 0, %74 ]
  ret i64 %82
}

; Function Attrs: nounwind
declare ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(ptr noundef returned) unnamed_addr #5

declare ptr @__cxa_begin_catch(ptr) local_unnamed_addr

declare void @_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv(ptr noundef) local_unnamed_addr #3

declare void @__cxa_end_catch() local_unnamed_addr

; Function Attrs: noinline noreturn nounwind ssp uwtable(sync)
define linkonce_odr hidden void @__clang_call_terminate(ptr noundef %0) local_unnamed_addr #6 {
  %2 = tail call ptr @__cxa_begin_catch(ptr %0) #14
  tail call void @_ZSt9terminatev() #15
  unreachable
}

; Function Attrs: cold nofree noreturn
declare void @_ZSt9terminatev() local_unnamed_addr #7

; Function Attrs: mustprogress noreturn ssp uwtable(sync)
define linkonce_odr hidden void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE20__throw_length_errorB9nqe210106Ev() local_unnamed_addr #8 {
  tail call void @_ZNSt3__120__throw_length_errorB9nqe210106EPKc(ptr noundef nonnull @.str.2) #16
  unreachable
}

; Function Attrs: inlinehint mustprogress noreturn ssp uwtable(sync)
define linkonce_odr hidden void @_ZNSt3__120__throw_length_errorB9nqe210106EPKc(ptr noundef %0) local_unnamed_addr #9 personality ptr @__gxx_personality_v0 {
  %2 = tail call ptr @__cxa_allocate_exception(i64 16) #14
  %3 = invoke ptr @_ZNSt12length_errorC1B9nqe210106EPKc(ptr noundef %2, ptr noundef %0)
          to label %4 unwind label %5

4:                                                ; preds = %1
  tail call void @__cxa_throw(ptr %2, ptr nonnull @_ZTISt12length_error, ptr nonnull @_ZNSt12length_errorD1Ev) #16
  unreachable

5:                                                ; preds = %1
  %6 = landingpad { ptr, i32 }
          cleanup
  tail call void @__cxa_free_exception(ptr %2) #14
  resume { ptr, i32 } %6
}

declare ptr @__cxa_allocate_exception(i64) local_unnamed_addr

; Function Attrs: mustprogress ssp uwtable(sync)
define linkonce_odr hidden ptr @_ZNSt12length_errorC1B9nqe210106EPKc(ptr noundef returned %0, ptr noundef %1) unnamed_addr #4 {
  %3 = tail call ptr @_ZNSt11logic_errorC2EPKc(ptr noundef %0, ptr noundef %1)
  store ptr getelementptr inbounds nuw inrange(-16, 24) (i8, ptr @_ZTVSt12length_error, i64 16), ptr %0, align 8, !tbaa !6
  ret ptr %0
}

declare void @__cxa_free_exception(ptr) local_unnamed_addr

; Function Attrs: nounwind
declare ptr @_ZNSt12length_errorD1Ev(ptr noundef returned) unnamed_addr #5

; Function Attrs: cold noreturn
declare void @__cxa_throw(ptr, ptr, ptr) local_unnamed_addr #10

declare ptr @_ZNSt11logic_errorC2EPKc(ptr noundef returned, ptr noundef) unnamed_addr #3

; Function Attrs: nobuiltin allocsize(0)
declare nonnull ptr @_Znwm(i64 noundef) local_unnamed_addr #11

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(ptr noundef) local_unnamed_addr #12

declare void @_ZNKSt3__18ios_base6getlocEv(ptr dead_on_unwind writable sret(%"class.std::__1::locale") align 8, ptr noundef) local_unnamed_addr #3

; Function Attrs: nounwind
declare ptr @_ZNSt3__16localeD1Ev(ptr noundef returned) unnamed_addr #5

declare ptr @_ZNKSt3__16locale9use_facetERNS0_2idE(ptr noundef, ptr noundef nonnull align 8 dereferenceable(12)) local_unnamed_addr #3

declare void @_ZNSt3__18ios_base5clearEj(ptr noundef, i32 noundef) local_unnamed_addr #3

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc(ptr noundef, i8 noundef signext) local_unnamed_addr #3

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv(ptr noundef) local_unnamed_addr #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr writeonly captures(none), i8, i64, i1 immarg) #13

attributes #0 = { mustprogress nofree norecurse nosync nounwind ssp willreturn memory(none) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #1 = { mustprogress norecurse ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #2 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #3 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #4 = { mustprogress ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #5 = { nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #6 = { noinline noreturn nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #7 = { cold nofree noreturn }
attributes #8 = { mustprogress noreturn ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #9 = { inlinehint mustprogress noreturn ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #10 = { cold noreturn }
attributes #11 = { nobuiltin allocsize(0) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #12 = { nobuiltin nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a" }
attributes #13 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #14 = { nounwind }
attributes #15 = { noreturn nounwind }
attributes #16 = { noreturn }
attributes #17 = { builtin allocsize(0) }
attributes #18 = { builtin nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 26, i32 5]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 21.0.0 (clang-2100.1.1.101)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"vtable pointer", !8, i64 0}
!8 = !{!"Simple C++ TBAA"}
!9 = !{!10, !11, i64 0}
!10 = !{!"_ZTSNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryE", !11, i64 0, !13, i64 8}
!11 = !{!"bool", !12, i64 0}
!12 = !{!"omnipotent char", !8, i64 0}
!13 = !{!"p1 _ZTSNSt3__113basic_ostreamIcNS_11char_traitsIcEEEE", !14, i64 0}
!14 = !{!"any pointer", !12, i64 0}
!15 = !{i8 0, i8 2}
!16 = !{}
!17 = !{!18, !14, i64 40}
!18 = !{!"_ZTSNSt3__18ios_baseE", !19, i64 8, !20, i64 16, !20, i64 24, !19, i64 32, !19, i64 36, !14, i64 40, !14, i64 48, !21, i64 56, !22, i64 64, !20, i64 72, !20, i64 80, !23, i64 88, !20, i64 96, !20, i64 104, !21, i64 112, !20, i64 120, !20, i64 128}
!19 = !{!"int", !12, i64 0}
!20 = !{!"long", !12, i64 0}
!21 = !{!"any p2 pointer", !14, i64 0}
!22 = !{!"p1 int", !14, i64 0}
!23 = !{!"p1 long", !14, i64 0}
!24 = !{!18, !19, i64 8}
!25 = !{!26, !19, i64 0}
!26 = !{!"_ZTSNSt3__118_SentinelValueFillINS_11char_traitsIcEEEE", !19, i64 0}
!27 = !{!18, !19, i64 32}
!28 = !{!18, !20, i64 24}
!29 = !{!12, !12, i64 0}
