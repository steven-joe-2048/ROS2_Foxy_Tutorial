from setuptools import setup

package_name = 'py_pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='caros',
    maintainer_email='caros@todo.todo',
    description='Examples of minimal publisher/subscriber using rclpy',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'talker = py_pubsub.publisher_member_function:main',
                'listener = py_pubsub.subscriber_member_function:main',
                'talker_new_intf = py_pubsub.publisher_member_function_new_intf:main',
                'listener_new_intf = py_pubsub.subscriber_member_function_new_intf:main',
        ],
    },
)
