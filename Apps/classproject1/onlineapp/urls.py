from django.urls import include, path
from onlineapp.views import CollegeView,AddCollegeView,AddStudentView,LoginView,logout_user,college_view,college_view1
from onlineapp.views import SignUpView,StudentApiView,TestView,CustomAuthToken

urlpatterns = [
    path('colleges/',CollegeView.as_view(),name="printcolleges"),
    path('colleges/<int:id>/',CollegeView.as_view(), name='students'),
    path('colleges/addcollege',AddCollegeView.as_view(),name="add_college"),
    path('colleges/edit/<int:pk>/',AddCollegeView.as_view(),name="edit_college"),
    path('colleges/delete/<int:pk>/',AddCollegeView.as_view(),name="delete_college"),
    path('student/add/<int:id>', AddStudentView.as_view(), name="add_student"),
    path('student/edit/<int:id>', AddStudentView.as_view(), name="edit_student"),
    path('student/del/<int:id>', AddStudentView.as_view(), name="del_student"),
    path('login',LoginView.as_view(),name="login"),
    path('signup',SignUpView.as_view(),name="signup"),
    path('logout',logout_user,name="logout"),
    path('api/colleges',college_view,name="apicolleges"),
    path('api/colleges/<int:cpk>',college_view1,name="apicollege"),
    path('api/colleges/<int:cid>/students',StudentApiView.as_view(),name="apstudents"),
    path('api/colleges/<int:cid>/students/<int:id>', StudentApiView.as_view(), name="apstudents"),
    path('api/authtoken/',CustomAuthToken.as_view(),name="authtoken"),
    path('testing/',TestView.as_view(),name="test")
]