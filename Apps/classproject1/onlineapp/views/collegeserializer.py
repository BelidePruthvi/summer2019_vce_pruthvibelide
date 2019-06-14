from rest_framework.decorators import api_view, authentication_classes, permission_classes
from onlineapp.models import *
from onlineapp.serializer import CollegeSerializer
from rest_framework import status
from rest_framework.permissions import IsAuthenticated
from rest_framework.authentication import SessionAuthentication, BasicAuthentication,TokenAuthentication
from rest_framework.authtoken.models import Token
from rest_framework.authtoken.views import ObtainAuthToken
from rest_framework.response import Response

@api_view(['GET','POST'])
@authentication_classes(( BasicAuthentication,SessionAuthentication,TokenAuthentication))
@permission_classes((IsAuthenticated,))
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
@authentication_classes(( BasicAuthentication,SessionAuthentication,TokenAuthentication))
@permission_classes((IsAuthenticated,))
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


class CustomAuthToken(ObtainAuthToken):

    def post(self, request, *args, **kwargs):
        serializer = self.serializer_class(data=request.data,context={'request': request})
        serializer.is_valid(raise_exception=True)
        user = serializer.validated_data['user']
        token, created = Token.objects.get_or_create(user=user)
        return Response({
            'token': token.key,
            'username': user.username,
            'password': user.password
        })