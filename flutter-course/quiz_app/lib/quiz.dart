import 'package:flutter/material.dart';
import 'package:quiz_app/questions_screen.dart';
import 'package:quiz_app/start_widget.dart';

const colors = [
  Color.fromARGB(255, 93, 20, 129),
  Color.fromARGB(255, 131, 29, 182),
];

class Quiz extends StatefulWidget {
  const Quiz({super.key});

  @override
  State<Quiz> createState() {
    return _QuizState();
  }
}

class _QuizState extends State<Quiz> {
  var activeScreen = 'START';

  void switchScreen() {
    setState(() {
      activeScreen = 'QUESTIONS';
    });
  }

  @override
  Widget build(context) {
    final screenWidget = activeScreen == 'START'
        ? LogoWidget(switchScreen)
        : const QuestionsWidget();

    return MaterialApp(
      home: Scaffold(
        body: Container(
          decoration: const BoxDecoration(
              gradient: LinearGradient(
            colors: colors,
            begin: Alignment.topCenter,
            end: Alignment.bottomCenter,
          )),
          child: Center(
            child: screenWidget,
          ),
        ),
      ),
    );
  }
}
