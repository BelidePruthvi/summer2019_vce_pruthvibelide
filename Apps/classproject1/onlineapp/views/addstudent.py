from django.views import View
from onlineapp.models import *
from django.shortcuts import render,redirect
from onlineapp.forms import *
from django.urls import resolve
from django.contrib.auth.mixins import LoginRequiredMixin,PermissionRequiredMixin

class AddStudentView(PermissionRequiredMixin,LoginRequiredMixin,View):
    login_url = 'login'
    permission_required = ('onlineapp.add_student','onlineapp.delete_student','onlineapp.change_student')

    def get(self, request, *args, **kwargs):

        student_form = AddStudent()
        mock_form = AddMock1()
        if resolve(request.path_info).url_name == 'edit_student':
            student = Student.objects.get(**kwargs)
            mock = MockTest1.objects.get(student=student)
            student_form = AddStudent(instance=student)
            mock_form = AddMock1(instance=mock)
        title = "Add Student"

        return render(request,
                      template_name="student_form.html",
                      context={
                          'title': title,
                          'student_form': student_form,
                          'mock_form': mock_form,
                      })

    def post(self, request, **kwargs):

        college = None
        student = None
        student_form = None
        mock = None
        mock_form = None
        if resolve(request.path_info).url_name == 'add_student':
            college = College(**kwargs)
            student = Student(college=college)
            student_form = AddStudent(request.POST, instance=student)

            if student_form.is_valid():
                student_form.save()
            total = sum([int(request.POST['problem' + str(i)]) for i in range(1, 5)])
            mock = MockTest1(student=student, total=total)

        if resolve(request.path_info).url_name == 'edit_student':
            student = Student.objects.get(**kwargs)
            kwargs['id'] = student.college.id
            student_form = AddStudent(request.POST, instance=student)
            if student_form.is_valid():
                student_form.save()
            total = sum([int(request.POST['problem' + str(i)]) for i in range(1, 5)])
            mock = MockTest1.objects.get(student=student)
            mock.total = total

        if resolve(request.path_info).url_name == 'del_student':
            student = Student.objects.get(**kwargs)
            kwargs['id'] = student.college.id
            m = MockTest1.objects.get(student=student)
            student.delete()
            m.delete()
            return redirect('students', **kwargs)

        mock_form = AddMock1(request.POST, instance=mock)

        if mock_form.is_valid():
            mock_form.save()
            return redirect('students', **kwargs)

        title = "Add Student"
        return render(request,
                      template_name="student_form.html",
                      context={
                          'title': title,
                          'student_form': student_form,
                          'mock_form': mock_form,
                      })