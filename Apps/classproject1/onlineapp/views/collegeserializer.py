from rest_framework.decorators import api_view
from onlineapp.models import *
from rest_framework.response import Response
from onlineapp.serializer import CollegeSerializer
from rest_framework import status

@api_view(['GET','POST'])
def college_view(request):
    if request.method=='GET':
        college=College.objects.all()
        serializer=CollegeSerializer(college,many=True)
        return Response(serializer.data)

    if request.method == 'POST':
        serializer =CollegeSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET','POST','PUT','DELETE'])
def college_view1(request,cpk):
    if request.method=='GET':
        college=College.objects.get(id=cpk)
        serializer=CollegeSerializer(college)
        return Response(serializer.data)

    if request.method=='PUT':
        c = College.objects.get(id=cpk)
        serializer = CollegeSerializer(c,data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    if request.method=='DELETE':
        c = College.objects.get(id=cpk)
        c.delete()
        return Response()

