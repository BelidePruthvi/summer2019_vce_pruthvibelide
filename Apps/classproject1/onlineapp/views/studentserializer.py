from onlineapp.models import *
from rest_framework.response import Response
from onlineapp.serializer import CollegeSerializer,StudentDetailsSerializer,MockTest1Serializer,StudentSerializer
from rest_framework import status
from rest_framework.views import APIView
from django.http import JsonResponse
from rest_framework.authentication import SessionAuthentication, BasicAuthentication,TokenAuthentication
from rest_framework.permissions import IsAuthenticated

class StudentApiView(APIView):
    authentication_classes = (SessionAuthentication, BasicAuthentication,TokenAuthentication)
    permission_classes = (IsAuthenticated,)
    def get(self, request, **kwargs):
        college = College.objects.get(id=kwargs["cid"])
        if 'id' in kwargs:
            students = Student.objects.filter(id=kwargs['id'])
        else:
            students = Student.objects.filter(college=college)
        serializer = StudentDetailsSerializer(students, many=True)
        return JsonResponse(serializer.data, safe=False)

    def post(self, request, **kwargs):
        college = College.objects.get(id=kwargs["cid"])
        student = Student(college=college)
        serializer = StudentSerializer(student, data=request.data)
        if serializer.is_valid():
            serializer.save()
        else:
            return JsonResponse(serializer.errors, status=400)
        data = serializer.data
        errors = serializer.errors
        if 'mocktest1' in request.data:
            mock1 = MockTest1(student=student)
            mockserializer = MockTest1Serializer(mock1, data=request.data['mocktest1'])
            if mockserializer.is_valid():
                mockserializer.save()
                data.update({'mocktest1': mockserializer.data})
                return JsonResponse(data, status=201)

            errors.update({'mocktest1': mockserializer.errors})

        elif serializer.is_valid():
            return JsonResponse(data, status=201)
        return JsonResponse(errors, status=400)

    def put(self, request, **kwargs):

        student = Student.objects.get(id=kwargs['id'])
        serializer = StudentSerializer(student, data=request.data)
        if serializer.is_valid():
            serializer.save()
        else:
            return JsonResponse(serializer.errors, status=400)
        data = serializer.data
        errors = serializer.errors
        if 'mocktest1' in request.data:
            try:
                mock1 = MockTest1.objects.get(student=student)
            except:
                mock1 = MockTest1(student=student)
            mockserializer = MockTest1Serializer(mock1, data=request.data['mocktest1'])
            if mockserializer.is_valid():
                mockserializer.save()
                data.update({'mocktest1': mockserializer.data})
                return JsonResponse(data, status=201)

            errors.update({'mocktest1': mockserializer.errors})

        elif serializer.is_valid():
            return JsonResponse(data, status=201)
        return JsonResponse(errors, status=400)

    def delete(self, request, **kwargs):
        student = Student.objects.get(id=kwargs['id'])
        student.delete()
        return Response()