pipeline {
    agent any

    stages {
        stage('Build') {
            step {
                echo 'Building ft_containers...'
                sh make
            }
        }

        stage('Test') {
            step {
                echo 'Testing ft_containers...'
            }
        }

        stage('Deploy') {
            step {
                echo 'Deploying ft_containers...'
            }
        }
    }
}