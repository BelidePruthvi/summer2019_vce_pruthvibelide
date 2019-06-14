from rest_framework import serializers
from onlineapp.models import College,Student,MockTest1

class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model=College
        fields=('name','location','acronym','contact')

class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Student
        fields = ('id', 'name', 'email',  'db_folder', 'dropped_out')

class MockTest1Serializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('problem1', 'problem2', 'problem3', 'problem4', 'total')


class StudentDetailsSerializer(serializers.ModelSerializer):
    mocktest1 = MockTest1Serializer(many=False, read_only=True)

    class Meta:
        model = Student
        fields = ('id', 'name', 'email', 'dob', 'db_folder', 'dropped_out', 'mocktest1')