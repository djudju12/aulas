import 'package:flutter/material.dart';
import 'package:quiz_app/text_widget.dart';

class AnswerButton extends StatelessWidget {
  final String data;
  final void Function() callback;
  const AnswerButton({required this.data, required this.callback, super.key});

  @override
  Widget build(context) {
    return ElevatedButton(
      onPressed: callback,
      style: ElevatedButton.styleFrom(
        padding: const EdgeInsets.symmetric(
          horizontal: 40,
          vertical: 10,
        ),
        backgroundColor: const Color.fromARGB(255, 64, 2, 110),
        foregroundColor: Colors.white,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(40),
        ),
      ),
      child: TextWidget(data),
    );
  }
}
